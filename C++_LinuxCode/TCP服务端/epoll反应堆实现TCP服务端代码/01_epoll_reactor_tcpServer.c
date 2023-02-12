#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*事件数组的长度	**/
#define GLOBAL_ARRAY_SIZE 1024

/*缓存大小	  **/
#define GLOBAL_BUFFER_SIZE 1024

/*全局epoll根节点   **/
int GLOBAL_EPOLL_NODE = -1;

/*全局统计客户端连接数量	**/
int GLOBAL_CLIENT_CONNECT_COUNT = 0;

/*事件类型	**/
typedef struct Epoll_event_type
{
	int   fd;
	int   event;
	void  (*pCallback)(int fd, int event, void* arg);
	void* arg;
	char  buf[GLOBAL_BUFFER_SIZE];
	int   bufLength;
}EventType;

/*事件数组		**/
EventType GLOBAL_EVENT_ARRAY[GLOBAL_ARRAY_SIZE];

/*添加事件函数  **/
void funcAddEvent(int fd, int event, void (*pCallback)(int, int, void*), EventType* pNode);

/*修改事件函数    **/
void funcModEvent(int fd, int event, void (*pCallback)(int, int, void *), EventType* pNode);

/*删除事件函数    **/
void funcDelEvent(int fd, int event, EventType* pNode);

/*接收客户端数据函数	**/
void funcRecvMessage(int fd, int event, void* arg);

/*发送数据到客户端函数  **/
void funcSendMessage(int fd, int event, void* arg);

/*接收客户端连接函数    **/
void funcAcceptNewClient(int fd, int event, void* arg);


/*添加事件函数	**/
void funcAddEvent(int fd, int event, void (*pCallback)(int, int, void*), EventType* pNode)
{
	/*节点参数设置	  **/
	pNode->fd = fd;
	pNode->event = event;
	pNode->pCallback = pCallback;
	pNode->arg = (void *)pNode;		/*将自身节点作为函数参数	**/

	/*节点加入epoll树	**/
	struct epoll_event epollNode;
	memset(&epollNode, 0, sizeof(epollNode));

	epollNode.data.ptr = (void *)pNode;
	epollNode.events = event;
	epoll_ctl(GLOBAL_EPOLL_NODE, EPOLL_CTL_ADD, fd, &epollNode);
}

/*修改事件函数	  **/
void funcModEvent(int fd, int event, void (*pCallback)(int, int, void *), EventType* pNode)
{
	/*修改事件节点参数	  **/
	pNode->fd = fd;
	pNode->event = event;
	pNode->pCallback = pCallback;

	/*修改epoll节点参数	  **/
	struct epoll_event epollNode;
	memset(&epollNode, 0, sizeof(epollNode));
	
	epollNode.data.ptr = (void *)pNode;
	epollNode.events = event;

	epoll_ctl(GLOBAL_EPOLL_NODE, EPOLL_CTL_MOD, fd, &epollNode);
}

/*删除事件函数	  **/
void funcDelEvent(int fd, int event, EventType* pNode)
{
	/*清空事件节点	  **/
	pNode->fd = 0;
	pNode->event = 0;
	pNode->pCallback = NULL;
	pNode->arg = NULL;
	memset(pNode->buf, 0, GLOBAL_BUFFER_SIZE);
	pNode->bufLength = 0;

	/*删除epoll节点	  **/
	struct epoll_event epollNode;
	memset(&epollNode, 0, sizeof(epollNode));

	epoll_ctl(GLOBAL_EPOLL_NODE, EPOLL_CTL_DEL, fd, &epollNode);
}


/*接收客户端数据函数    **/
void funcRecvMessage(int fd, int event, void* arg)
{
	EventType* pEventNode = (EventType *)arg;

	char recvBuf[1024] = "\0";	
	int readSize = read(fd, recvBuf, sizeof(recvBuf));
	if(-1 == readSize)
	{
		perror("read() error");

		funcDelEvent(fd, event, pEventNode);
		--GLOBAL_CLIENT_CONNECT_COUNT;

		return;
	}
	else if(0 == readSize)
	{
		printf("client disconnect\n");

		funcDelEvent(fd, event, pEventNode);
		--GLOBAL_CLIENT_CONNECT_COUNT;

		return;
	}
	else
		printf("recv: %s", recvBuf);
	
	/*填充即将要发送的数据	  **/
	strncpy(pEventNode->buf, "200 ok\n", 7);
	pEventNode->bufLength = 7;
	
	/*修改节点状态	**/
	funcModEvent(fd, EPOLLOUT, funcSendMessage, pEventNode);
}

/*发送数据到客户端函数  **/
void funcSendMessage(int fd, int event, void* arg)
{
	EventType* pEventNode = (EventType *)arg;

	write(fd, pEventNode->buf, pEventNode->bufLength);
	
	/*切换事件类型	  **/
	funcModEvent(fd, EPOLLIN, funcRecvMessage, pEventNode);
}

/*接收客户端连接函数	**/
void funcAcceptNewClient(int fd, int event, void* arg)
{
	/*接收客户端连接	**/
	struct sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(clientAddr));

	socklen_t addrLength = sizeof(clientAddr);

	int clientSockId = accept(fd, (struct sockaddr *)&clientAddr, &addrLength);
	if(-1 == clientSockId)
	{
		perror("accept() error");
		return;
	}
	else
	{
		char sIp[16] = "\0";
		inet_ntop(AF_INET, &clientAddr.sin_addr, sIp, INET_ADDRSTRLEN);

		int port = ntohs(clientAddr.sin_port); 

		printf("new client connect. ip: %s port: %d\n", sIp, port);
	}

	/*查找为被分配的自定义类型节点	  **/
	EventType* pEventNode = NULL;
	for(int i = 1; i < GLOBAL_ARRAY_SIZE; ++i)
	{
		if(0 == GLOBAL_EVENT_ARRAY[i].fd)
		{
			pEventNode = &GLOBAL_EVENT_ARRAY[i];
			break;
		}
	}

	if(NULL == pEventNode)
	{
		printf("search empty event node error. array is full.\n");
		return;		
	}

	/*添加事件	**/
	funcAddEvent(clientSockId, EPOLLIN, funcRecvMessage, pEventNode);

	/*增加客户端计数	**/
	++GLOBAL_CLIENT_CONNECT_COUNT;
}


int main()
{
	/*创建socket 	**/
	int sockId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(-1 == sockId)
	{
		perror("socket() error");
		return -1;
	}

	/*绑定socket 	**/
	struct sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));

	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(8000);
   	sockAddr.sin_addr.s_addr = inet_addr("192.168.0.188");

	int bindRet = bind(sockId, (struct sockaddr *)&sockAddr, sizeof(sockAddr));
	if(-1 == bindRet)
	{
		perror("bind() error");

		close(sockId);
		return -1;
	}

	/*监听socket	**/
	int listenRet = listen(sockId, 1024);
	if(-1 == listenRet)
	{
		perror("listen() error");

		close(sockId);
		return -1;
	}

	/*epoll初始化	**/
	GLOBAL_EPOLL_NODE = epoll_create(1);
	if(-1 == GLOBAL_EPOLL_NODE)
	{
		perror("epoll_create() error");

		close(sockId);
		return -1;
	}
	
	/*添加接收客户端新建立连接的事件	**/
	funcAddEvent(sockId, EPOLLIN, funcAcceptNewClient, &GLOBAL_EVENT_ARRAY[0]);

	/*创建存放epoll事件的数组	  **/
	struct epoll_event epollNodeArray[GLOBAL_ARRAY_SIZE];
	memset(epollNodeArray, 0, sizeof(epollNodeArray));

	/*通过epoll_wait()函数完成与客户端的交互	**/
	while(true)
	{
		int readyEvntSize = epoll_wait(GLOBAL_EPOLL_NODE, epollNodeArray, GLOBAL_ARRAY_SIZE, -1);
		if(-1 == readyEvntSize)
		{
			perror("epoll_wait() error");
			break;
		}
			
		for(int i = 0; i < readyEvntSize; ++i)
		{
			/*获取epoll节点中存储的自定义类型节点	**/
			EventType* pNode = (EventType *)epollNodeArray[i].data.ptr;

			/*判断epoll返回的事件类型与添加节点存储的事件类型是否一致	**/
			if(pNode->event & epollNodeArray[i].events)
				pNode->pCallback(pNode->fd, pNode->event, (void*)pNode);
		}

		if(0 == GLOBAL_CLIENT_CONNECT_COUNT)
		{
			printf("all client disconnect server. server quit\n");
			break;
		}
	}

	close(sockId);
	close(GLOBAL_EPOLL_NODE);

	return 0;
}
