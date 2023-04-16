#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <event.h>
#include <event2/listener.h>

/*回调函数：接受客户端的连接            **/
void funcCbAccept(struct evconnlistener* pListener, evutil_socket_t fd, struct sockaddr* pAddr, int socklen, void* arg);

/*回调函数：读取数据                    **/
void funcCbRead(struct bufferevent* bev, void* ctx);

/*回调函数：写入数据                    **/
void funcCbWrite(struct bufferevent* bev, void* ctx);

/*回调函数：异常处理                    **/
void funcCbError(struct bufferevent* bev, short what, void* ctx);

/*回调函数：信号处理					**/
void funcCbSignal(evutil_socket_t sig, short events, void* arg);


/*回调函数：接受客户端的连接			**/
void funcCbAccept(struct evconnlistener* pListener, evutil_socket_t fd, struct sockaddr* pAddr, int socklen, void* arg)
{
	struct event_base* pEvBase = (struct event_base *)arg;

	/*创建bufferevent					**/
	struct bufferevent* pBuffer = bufferevent_socket_new(pEvBase, fd, BEV_OPT_CLOSE_ON_FREE);

	/*监听读、写、异常事件				**/
	bufferevent_setcb(pBuffer, funcCbRead, funcCbWrite, funcCbError, NULL);

	/*等待接收客户端消息后再使能写监听	**/
	bufferevent_enable(pBuffer, EV_READ);
	bufferevent_enable(pBuffer, EV_WRITE);

	/*打印客户端信息					**/
	char addr[16] = "\0";
	struct sockaddr_in* pSockAddr = (struct sockaddr_in *)pAddr; 
	inet_ntop(AF_INET, &(pSockAddr->sin_addr.s_addr), addr, INET_ADDRSTRLEN);

	int port = ntohs(pSockAddr->sin_port);

	printf("new client connect server. ip: %s port: %d\n", addr, port);
}

/*回调函数：读取数据					**/
void funcCbRead(struct bufferevent* bev, void* ctx)
{
	char data[128] = "\0";
	memset(data, 0, sizeof(data));

	bufferevent_read(bev, data, sizeof(data));

	printf("recv: %s", data);

	/*收到客户端消息使能写监听			**/
	bufferevent_enable(bev, EV_WRITE);
}

/*回调函数：写入数据					**/
void funcCbWrite(struct bufferevent* bev, void* ctx)
{
	printf("send: %s", "200 ok\n");
	bufferevent_write(bev, "200 ok\n", strlen("200 ok\n"));

	/*发送数据后使写监听失效			**/
	bufferevent_disable(bev, EV_WRITE);
}

/*回调函数：异常处理					**/
void funcCbError(struct bufferevent* bev, short what, void* ctx)
{
	if(BEV_EVENT_EOF & what)
		printf("client disconnect\n");
	else if(BEV_EVENT_READING & what)
		perror("read data error");
	else if(BEV_EVENT_WRITING & what)
		perror("write data error");
	else
		printf("other error\n");

	bufferevent_free(bev);
}

/*回调函数：信号处理                    **/
void funcCbSignal(evutil_socket_t sig, short events, void* arg)
{
	struct event_base* pEvBase = (struct event_base *)arg;
	struct timeval delay = {1, 0};

	printf("server will exit\n");
	event_base_loopexit(pEvBase, &delay);
}


int main()
{
	/*创建event_base根基				**/
	struct event_base* pEvBase = event_base_new();
	if(NULL == pEvBase)
		return -1;
		
	/*通过evconnlistener创建socket		**/
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(8001);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	struct evconnlistener* pListener = evconnlistener_new_bind(pEvBase, funcCbAccept, (void *)pEvBase, LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1, (const struct sockaddr*)&addr, sizeof(addr));

	/*注册服务端退出信号事件			**/
	struct event* pSignal = evsignal_new(pEvBase, SIGINT, funcCbSignal, (void *)pEvBase);
	evsignal_add(pSignal, NULL);

	/*进入事件循环						**/
	event_base_dispatch(pEvBase);

	/*销毁事件							**/
	event_del(pSignal);
	event_free(pSignal);

	/*销毁evconnlistener				**/
	evconnlistener_free(pListener);

	/*销毁event_base根基				**/
	event_base_free(pEvBase);

	return 0;
}
