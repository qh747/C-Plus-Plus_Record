#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

typedef struct SOCK_INFO
{
	int                m_sockFd;
	struct sockaddr_in m_sockAddr;
}SockInfo;

void* threadFunc(void* arg)
{
	SockInfo* pSockInfo = (SockInfo *)arg;
	
	char ipAddr[16] = "\0";
	inet_ntop(AF_INET, &(pSockInfo->m_sockAddr.sin_addr), ipAddr, INET_ADDRSTRLEN);

	int port = ntohs(pSockInfo->m_sockAddr.sin_port);

	printf("new client connect server. ip: %s port: %d\n", ipAddr, port);

	char recvBuf[128] = "\0";
	char sendBuf[64] = "server recv success\n";
	
	while(true)
	{
		int recvSize = read(pSockInfo->m_sockFd, recvBuf, sizeof(recvBuf));
		if(-1 == recvSize)
		{
			printf("recv error\n");
			break;
		}
		else if(0 == recvSize)
		{
			printf("client disconnect\n");
			break;
		}

		printf("recv: %s", recvBuf);

		write(pSockInfo->m_sockFd, sendBuf, sizeof(sendBuf));
	}
	
	free(pSockInfo);
	return NULL;
}

int main()
{
	/*创建Socket套接字	**/
	int sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockFd)
	{
		perror("socket() error");
		return -1;
	}

	/*绑定	**/
	struct sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));

	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(8000);
	sockAddr.sin_addr.s_addr = inet_addr("192.168.0.188");

	int bindRet = bind(sockFd, (struct sockaddr *)&sockAddr, sizeof(sockAddr));
	if(-1 == bindRet)
	{
		perror("bind() error");

		close(sockFd);
		return -1;
	}

	/*监听	**/
	int listenRet = listen(sockFd, 1024);
	if(-1 == listenRet)
	{
		perror("listen() error");

		close(sockFd);
		return -1;
	}

	/*接受客户端连接	**/
	SockInfo* pSockInfo = NULL;
	
	pthread_attr_t threadAttr;
	pthread_attr_init(&threadAttr);
	pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);

	while(true)
	{
		struct sockaddr_in clientAddr;
		memset(&clientAddr, 0, sizeof(clientAddr));

		socklen_t clientAddrLen = sizeof(clientAddr);

		int clientFd = accept(sockFd, (struct sockaddr *)&clientAddr, &clientAddrLen);
		if(-1 == clientFd)
		{
			if((ECONNABORTED == errno) || (EINTR == errno))
				continue;
			else
				break;
		}

		pSockInfo = malloc(sizeof(SockInfo));
		pSockInfo->m_sockFd = clientFd;
		pSockInfo->m_sockAddr = clientAddr;

		pthread_t threadId = -1;
		pthread_create(&threadId, &threadAttr, threadFunc, (void *)pSockInfo);
	}

	/*关闭	**/
	pthread_attr_destroy(&threadAttr);
	close(sockFd);

	return 0;
}
