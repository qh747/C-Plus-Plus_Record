#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	/*创建Socket    **/
	int sockId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(-1 == sockId)
	{
		perror("socket() error");
		return -1;
	}

	/*绑定Socket	**/
	struct sockaddr_in ipAddr;
	memset(&ipAddr, 0, sizeof(ipAddr));

	ipAddr.sin_family = AF_INET;
	ipAddr.sin_port = htons(8000);
	ipAddr.sin_addr.s_addr = inet_addr("192.168.0.188");

	int bindRet = bind(sockId, (struct sockaddr *)&ipAddr, sizeof(ipAddr));
	if(-1 == bindRet)
	{
		perror("bind() error");
		close(sockId);
		
		return -1;
	}

	/*监听Socket	**/
	int listenRet = listen(sockId, 4);
	if(-1 == listenRet)
	{
		perror("lesten() error");
		close(sockId);

		return -1;
	}

	/*接收客户端消息	**/
	int epollId = epoll_create(1);
	if(-1 == epollId)
	{
		perror("epoll_create() error");
		close(sockId);

		return -1;
	}

	struct epoll_event epollNode;
	memset(&epollNode, 0, sizeof(epollNode));

	epollNode.events = EPOLLIN;
	epollNode.data.fd = sockId;

	epoll_ctl(epollId, EPOLL_CTL_ADD, sockId, &epollNode);

	int newClientCount = 0;
	while(true)
	{
		struct epoll_event epollEventArray[16];
		memset(epollEventArray, 0, sizeof(epollEventArray));

		int readyEventCount = epoll_wait(epollId, epollEventArray, 16, -1);
		if(-1 == readyEventCount)
		{
			perror("epoll_wait() error");
			continue;
		}
		
		bool isServerExit = false;
		for(int i = 0; i < readyEventCount; ++i)
		{
			if(sockId == epollEventArray[i].data.fd)
			{
				/*新客户端接入	  **/
				struct sockaddr_in clientAddr;
				memset(&clientAddr, 0, sizeof(clientAddr));

				socklen_t addrSize = sizeof(clientAddr);

				int newClientId = accept(sockId, (struct sockaddr *)&clientAddr, &addrSize);
				if(-1 == newClientId)
				{
					perror("accept() error");
					continue;
				}
				else
				{
					char ipBuf[16] = "\0";
					inet_ntop(AF_INET, &clientAddr.sin_addr, ipBuf, INET_ADDRSTRLEN);

					int port = ntohs(clientAddr.sin_port);

					printf("new client connect. ip: %s port: %d\n", ipBuf, port);
				}

				struct epoll_event epollNewNode;
			   	memset(&epollNewNode, 0, sizeof(epollNewNode));

				epollNewNode.events = EPOLLIN;
				epollNewNode.data.fd = newClientId;

				epoll_ctl(epollId, EPOLL_CTL_ADD, newClientId, &epollNewNode);
				
				++newClientCount;				
			}
			else
			{
				/*客户端发送数据	**/
				char recvBuf[32] = "\0";
				int readRet = read(epollEventArray[i].data.fd, recvBuf, sizeof(recvBuf));
				if(-1 == readRet)
				{
					perror("read() error");

					epoll_ctl(epollId, EPOLL_CTL_DEL, epollEventArray[i].data.fd, &epollEventArray[i]);
					continue;
				}
				else if(0 == readRet)
				{
					/*客户端退出	**/
					printf("client disconnect\n");

					epoll_ctl(epollId, EPOLL_CTL_DEL, epollEventArray[i].data.fd, &epollEventArray[i]);
					close(epollEventArray[i].data.fd);
					if(0 == --newClientCount)
						isServerExit = true;
				}
				else
				{
					printf("recv: %s", recvBuf);

					write(epollEventArray[i].data.fd, "200 ok\n", strlen("200 ok\n"));
				}
			}
		}
		
		if(true == isServerExit)
		{
			printf("all clients have exit. server exit.\n");
			break;
		}
	}

	/*关闭Socket	**/
	close(sockId);

	return 0;
}
