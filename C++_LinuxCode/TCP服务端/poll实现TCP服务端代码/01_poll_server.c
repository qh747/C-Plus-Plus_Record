#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>

/*宏定义，最大的服务端连接数量	**/
const int GLOBAL_MAX_COUNT = 1024;

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

	/*poll集合处初始化	**/
	struct pollfd pollArray[GLOBAL_MAX_COUNT];
	for(int i = 0; i < GLOBAL_MAX_COUNT; ++i)
	{
		pollArray[i].fd = -1;
	}

	struct pollfd listenPollFd;
	memset(&listenPollFd, 0, sizeof(listenPollFd));

	listenPollFd.fd = sockfd;
	listenPollFd.events = POLLIN;

	pollArray[0] = listenPollFd;

	/*处理客户端请求	**/
	int pollSize = 1;
	int currentConnectCount = 0;
	while(true)
	{
		int pollRet = poll(pollArray, pollSize, -1);
		if(-1 == pollRet)
		{
			perror("poll() error");
			break;
		}
		else if(0 == pollRet)
		{
			continue;
		}

		/*判断是否有新客户端接入	**/
		if(1 == (pollArray[0].revents & POLLIN))
		{
			struct sockaddr_in clientAddr;
			memset(&clientAddr, 0, sizeof(clientAddr));

			socklen_t addrLen = sizeof(clientAddr);
			int clientSockFd = accept(sockfd, (struct sockaddr *)&clientAddr, &addrLen);
			if(-1 == clientSockFd)
			{
				perror("accept() error");
				break;
			}			

			char ipAddr[16] = "\0";
			inet_ntop(AF_INET, &clientAddr.sin_addr.s_addr, ipAddr, INET_ADDRSTRLEN);
			int port = ntohs(clientAddr.sin_port);
			printf("new client connect server.ip: %s port: %d\n", ipAddr, port);

			struct pollfd clientPollFd;
			memset(&clientPollFd, 0, sizeof(clientPollFd));

			clientPollFd.fd = clientSockFd;
			clientPollFd.events = POLLIN;

			int i = 1;
			for(; i < GLOBAL_MAX_COUNT; ++i)
			{
				if(-1 == pollArray[i].fd)
				{
					pollArray[i] = clientPollFd;
					break;
				}
			}
			if(GLOBAL_MAX_COUNT == i)
			{
				printf("client connect count is max\n ");
				continue;
			}

			++currentConnectCount;
			++pollSize;

			if(0 == (--pollRet))
				continue;
		}

		/*判断是否有客户端数据可读取	**/
		for(int i = 1; i <= pollSize; ++i)
		{
			if(-1 == pollArray[i].fd)
				continue;

			if(1 != (pollArray[i].revents & POLLIN))
				continue;

			char recvBuf[64] = "\0";
			char sendBuf[16] = "recv success\n";

			int readRet = read(pollArray[i].fd, recvBuf, sizeof(recvBuf));
			if(-1 == readRet)
			{
				perror("read() error");

				close(pollArray[i].fd);
				
				int j = i;
				for(; j < (pollSize - 1); ++j)
				{
					pollArray[j] = pollArray[j + 1];
				}
				pollArray[j].fd = -1;
				
				--pollSize;
				--currentConnectCount;
			}
			else if(0 == readRet)
			{
				printf("client disconect server\n");
				close(pollArray[i].fd);
			
				int j = i;	
				for(; j < (pollSize - 1); ++j)
                {
                    pollArray[j] = pollArray[j + 1];
                }
				pollArray[j].fd = -1;
				
				--pollSize;
				--currentConnectCount;
			}
			else
			{
				printf("recv:%s", recvBuf);

				write(pollArray[i].fd, sendBuf, sizeof(sendBuf));
			}
		}

		/*判断是否满足服务端退出状态	**/
		if(0 == currentConnectCount)
		{
			printf("all clients disconnect server. server quit\n");
			break;
		}
	}

	close(sockfd);
	return 0;
}
