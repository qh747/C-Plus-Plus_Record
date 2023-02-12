#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	/*创建socket	**/
	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(-1 == sockfd)
	{
		perror("socket() error");
		return -1;
	}

	/*绑定	**/
	struct sockaddr_in ipAddr;
	memset(&ipAddr, 0, sizeof(ipAddr));

	ipAddr.sin_family = AF_INET;
	ipAddr.sin_port = htons(8000);
	ipAddr.sin_addr.s_addr = inet_addr("192.168.0.188");

	int bindRet = bind(sockfd, (struct sockaddr *)&ipAddr, sizeof(ipAddr));
	if(-1 == bindRet)
	{
		perror("bind() error");
		return -1;
	}

	/*监听	**/
	int listenRet = listen(sockfd, 1024);
	if(-1 == listenRet)
	{
		perror("listen() error");
		return -1;
	}

	/*select处理流程	**/
	fd_set selectSet;
	FD_ZERO(&selectSet);

	FD_SET(sockfd, &selectSet);

	fd_set tempSet;
	FD_ZERO(&tempSet);

	int maxFd = sockfd;

	int connectCount = 0;
	while(true)
	{
		tempSet = selectSet;
		int selectRet = select(maxFd+1, &tempSet, NULL, NULL, NULL);
	
		if(-1 == selectRet)
		{
			perror("select() error");
			break;
		}
		else if(0 == selectRet)
		{
			continue;
		}
		
		/*判断是否是连接套接字	**/
		if(0 != FD_ISSET(sockfd, &tempSet))
		{
			struct sockaddr_in clientAddr;
			memset(&clientAddr, 0, sizeof(clientAddr));

			socklen_t addrLen = sizeof(clientAddr);

			int clientfd = accept(sockfd, (struct sockaddr *)&clientAddr, &addrLen);
			if(-1 == clientfd)
			{
				continue;
			}

			char ipAddr[16] = "\0";
			inet_ntop(AF_INET, &clientAddr.sin_addr.s_addr, ipAddr, INET_ADDRSTRLEN);
			int port = ntohs(clientAddr.sin_port);
			printf("new client connect server. ip: %s port: %d\n", ipAddr, port);

			++connectCount;

			FD_SET(clientfd, &selectSet);
			
			if(clientfd > maxFd)
				maxFd = clientfd;

			if(0 == (selectRet - 1))
				continue;
		}

		/*判断是否有通信套接字	**/
		for(int i = sockfd + 1; i <= maxFd; ++i)
		{
			if(0 == FD_ISSET(i, &tempSet))	
				continue;

			char recvBuf[64] = "\0";
			char sendBuf[16] = "recv success\n";

			int readRet = read(i, recvBuf, sizeof(recvBuf));
			if(-1 == readRet)
			{
				perror("read() error");

				close(i);
				FD_CLR(i, &selectSet);

				--connectCount;
			}
			else if(0 == readRet)
			{
				printf("client disconnect server\n");

				close(i);
				FD_CLR(i, &selectSet);

				--connectCount;
			}
			else
			{
				printf("recv: %s", recvBuf);

				write(i, sendBuf, sizeof(sendBuf));
			}
		}

		/*判断是否满足退出条件	**/
		if(0 == connectCount)
			break;
	}

	close(sockfd);
	return 0;
}
