#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

/*TCP客户端函数    **/
int tcpClientFunc();

int main()
{
	int tcp_client_func_ret = tcpClientFunc();

	return 0;
}

int tcpClientFunc()
{
	/*创建TCP Socket    **/
	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(-1 == sockfd)
	{
		perror("socket() error");
		return -1;
	}

	/*连接TCP SERVER    **/
	struct sockaddr_in serverIpAddr;
	memset(&serverIpAddr, 0, sizeof(serverIpAddr));

	serverIpAddr.sin_family = AF_INET;
	serverIpAddr.sin_port = htons(1027);
	serverIpAddr.sin_addr.s_addr = inet_addr("192.168.0.188");
		
	int connect_ret = connect(sockfd, (struct sockaddr *)&serverIpAddr, sizeof(serverIpAddr));
	if(-1 == connect_ret)
	{
		perror("connect() error");
		return -1;
	}

	/*与TCP Server通信    **/
	char sendBuf[64] = "\0";
	char recvBuf[64] = "\0";
	
	while(true)
	{
		/*捕获用户输入数据, 使用fgets()函数会捕获到换行符, 因此输出时不需要在末尾加\n    **/
		printf("input: ");
		fgets(sendBuf, sizeof(sendBuf), stdin);

		/*发送数据     **/
		int sendBufSize = strlen(sendBuf);
		int sendSize = write(sockfd, sendBuf, sendBufSize);
		printf("client buf size: %d send size: %d send: %s", sendBufSize, sendSize, sendBuf);
		
		/*阻塞并等待服务端返回数据    **/
		if(0 != strncmp("quit", sendBuf, 4))
        {
			int recvSize = read(sockfd, recvBuf, sizeof(recvBuf));
			printf("client recv size: %d recv: %s\n", recvSize, recvBuf);
		}
		else
		{
			printf("client disconnect\n");
			break;
		}

		/*清空本次通信缓存    **/
        memset(recvBuf, 0, sizeof(recvBuf));
        memset(sendBuf, 0, sizeof(sendBuf));
	}

	/*关闭TCP Socket    **/
	close(sockfd);

	return 0;
}
