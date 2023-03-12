#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
	/*创建客户端套接字		**/
	int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(-1 == sockfd)
	{
		perror("socket() error");
		return -1;
	}

	/*绑定套接字			**/
	struct sockaddr_in clientAddr;
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(9000);
	clientAddr.sin_addr.s_addr = inet_addr("192.168.0.194");

	int bindRet = bind(sockfd, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
	if(-1 == bindRet)
	{
		perror("bind() error");
		return -1;
	}

	/*与客户端通信			**/
	char buf[1024] = "\0";
	memset(buf, 0, sizeof(buf));

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.0.194");

	socklen_t addrLen = sizeof(serverAddr);

	while(true)
	{
		/*捕获用户输入			**/
		printf("input(enter q to exit): ");
		fgets(buf, sizeof(buf), stdin);

		/*发送数据处理      **/
        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&serverAddr, addrLen);

		/*手动指定客户端退出的方式		**/
		if(0 == strncmp("q", buf, 1))
		{
			printf("client exit\n");
			break;
		}
		
		/*接收数据处理      **/
		memset(buf, 0, sizeof(buf));
		int recvSize = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&serverAddr, &addrLen);
		if(recvSize < 0)
		{
			perror("recvfrom() error");
			break;
		}
		else if(0 == recvSize)
		{
			printf("client disconnect\n");
			break;
		}
		else
		{
			char ipBuf[16] = "\0";
			inet_ntop(AF_INET, &serverAddr.sin_addr.s_addr, ipBuf, INET_ADDRSTRLEN);
			
			int port = ntohs(serverAddr.sin_port);
			
			printf("recv server ip: %s port: %d data: %s", ipBuf, port, buf);

			/*清空本轮数据缓存	**/
			memset(&buf, 0, sizeof(buf));
		}
	}

	/*关闭套接字			**/
	close(sockfd);
	return 0;
}
