#include <stdio.h>
#include <event.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

/*事件数组最大容量				**/
#define MAX_ARRAY_SIZE 1024

/*事件类型						**/
typedef struct DATE_TYPE_EVENT
{
	int fd;
	struct event* pEvent;
}Event_dt;

/*全局事件数组					**/
Event_dt GLOBAL_EVENT_ARRAY[MAX_ARRAY_SIZE];

/*记录客户端连接数量			**/
int GLOBAL_CONNECT_COUNT = 0;

/*初始化事件数组				**/
void funcInitEventArray(Event_dt* pArray, int size)
{
	for(int i = 0; i < size; ++i)
	{
		pArray[i].fd = 0;
		pArray[i].pEvent = NULL;
	}
}

/*清空事件数组					**/
void funcClearEventArray(Event_dt* pArray, int size)
{
	for(int i = 0; i < size; ++i)
	{
		if(0 != pArray[i].fd)
		{
			event_del(pArray[i].pEvent);
			event_free(pArray[i].pEvent);

			close(pArray[i].fd);
		}
	}

	memset(pArray, 0, sizeof(Event_dt) * size);
}

/*获取空的事件					**/
Event_dt* funcGetEmptyEvent(Event_dt* pArray, int size)
{
	for(int i = 0; i < size; ++i)
	{
		if(0 == pArray[i].fd)
			return &pArray[i];	
	}

	return NULL;
}

/*通过文件描述符获取事件		**/
Event_dt* funcGetEventByFd(Event_dt* pArray, int size, int fd)
{
	for(int i = 0; i < size; ++i)
	{
		if(fd == pArray[i].fd)
			return &pArray[i];
	}

	return NULL;
}

/*读取客户端数据				**/
void funcReadData(int fd, short events, void* arg)
{
	char buf[128] = "\0";
	memset(buf, 0, sizeof(buf));

	int readSize = read(fd, buf, sizeof(buf));
	if(-1 == readSize)
	{
		perror("read() error");

		Event_dt* pEv = funcGetEventByFd(GLOBAL_EVENT_ARRAY, MAX_ARRAY_SIZE, fd);
		event_del(pEv->pEvent);
		event_free(pEv->pEvent);

		close(fd);

		pEv->fd = 0;
		pEv->pEvent = NULL;

		--GLOBAL_CONNECT_COUNT;
	}
	else if(0 == readSize)
	{
		printf("client disconnect\n");

		Event_dt* pEv = funcGetEventByFd(GLOBAL_EVENT_ARRAY, MAX_ARRAY_SIZE, fd);
        event_del(pEv->pEvent);
        event_free(pEv->pEvent);

        close(fd);

        pEv->fd = 0;
        pEv->pEvent = NULL;

        --GLOBAL_CONNECT_COUNT;
	}
	else
	{
		printf("recv: %s", buf);
		write(fd, "200 ok\n", strlen("200 ok\n"));
	}

	if(GLOBAL_CONNECT_COUNT <= 0)
		event_base_loopbreak((struct event_base *)arg);
}

/*接受新客户端连接函数			**/
void funcAcceptNewClient(int fd, short events, void* arg)
{
	struct sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(clientAddr));

	socklen_t addrLen = sizeof(clientAddr);

	int clientfd = accept(fd, (struct sockaddr *)&clientAddr, &addrLen);
	if(-1 == clientfd)
	{
		perror("accept() error");
		return;
	}
	else
	{
		char ipAddr[16] = "\0";
		inet_ntop(AF_INET, &clientAddr.sin_addr, ipAddr, INET_ADDRSTRLEN);

		int port = ntohs(clientAddr.sin_port);
		
		printf("new client %s %d connect server\n", ipAddr, port);
	}

	struct event* pEv = event_new((struct event_base *)arg, clientfd, EV_READ | EV_PERSIST, funcReadData, arg);
	event_add(pEv, NULL);

	Event_dt* pEmptyEvent = funcGetEmptyEvent(GLOBAL_EVENT_ARRAY, MAX_ARRAY_SIZE);
	pEmptyEvent->fd = clientfd;
	pEmptyEvent->pEvent = pEv;
	
	++GLOBAL_CONNECT_COUNT;
}


int main()
{
	/*事件数组初始化			**/
	funcInitEventArray(GLOBAL_EVENT_ARRAY, MAX_ARRAY_SIZE);

	/*创建socket				**/
	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(-1 == sockfd)
	{
		perror("socket() error");
		return -1;
	}

	/*绑定socket				**/
	struct sockaddr_in sockAddr;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(8000);
	sockAddr.sin_addr.s_addr = inet_addr("192.168.0.194");

	int bindRet = bind(sockfd, (struct sockaddr *)&sockAddr, sizeof(sockAddr));
	if(-1 == bindRet)
	{
		perror("bind() error");

		close(sockfd);
		return -1;
	}

	/*监听socket				**/
	int listenRet = listen(sockfd, 1024);
	if(-1 == listenRet)
	{
		perror("listen() error");

		close(sockfd);
		return -1;
	}

	/*libevent句柄初始化		**/
	struct event_base* pEvBase = event_base_new();
	if(NULL == pEvBase)
	{
		printf("event_base_new() error\n");

		close(sockfd);
		return -1;
	}

	/*添加客户端连接事件		**/
	struct event* pEvent = event_new(pEvBase, sockfd, EV_READ | EV_PERSIST, funcAcceptNewClient, (void *)pEvBase);
	event_add(pEvent, NULL);

	/*事件循环					**/
	event_base_dispatch(pEvBase);

	/*事件循环退出后释放事件	**/
	funcClearEventArray(GLOBAL_EVENT_ARRAY, MAX_ARRAY_SIZE);
	event_del(pEvent);
	event_free(pEvent);
	event_base_free(pEvBase);

	/*关闭套接字				**/
	close(sockfd);

	return 0;
}
