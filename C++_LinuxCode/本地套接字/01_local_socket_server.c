#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main()
{
	/*创建套接字		**/
	int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		perror("socket() error");
		return -1;
	}

	/*绑定套接字		**/
	struct sockaddr_un servAddr;
	servAddr.sun_family = AF_UNIX;
	strcpy(servAddr.sun_path, "socket.serv");

	socklen_t addrLen = sizeof(servAddr);

	/*取消之前创建的文件	**/
	unlink("socket.serv");
	int bindRet = bind(sockfd, (struct sockaddr *)&servAddr, addrLen);
	if(-1 == bindRet)
	{
		perror("bind() error");
		close(sockfd);

		return -1;
	}

	/*监听套接字			**/
	int listenRet = listen(sockfd, 4);
	if(-1 == listenRet)
	{
		perror("listen() error");
		close(sockfd);

		return -1;
	}

	/*获取客户端连接		**/
	struct sockaddr_un cltAddr;
	socklen_t cltAddrLen;

	int cltfd = accept(sockfd, (struct sockaddr *)&cltAddr, &cltAddrLen);
	if(-1 == cltfd)
	{
		perror("accept() error");
		close(sockfd);

		return -1;
	}
	else
		printf("new client %s connect server\n", cltAddr.sun_path);

	/*与客户端通信			**/
	char buf[64] = "\0";
	memset(buf, 0, sizeof(buf));
	
	while(true)
	{
		int recvSize = read(cltfd, buf, sizeof(buf));
		if(recvSize < 0)
		{
			perror("read() error");
			break;
		}
		else if(0 == recvSize)
		{
			printf("client disconnect server\n");
			break;
		}
		else
		{
			printf("server recv: %s", buf);
			memset(buf, 0, sizeof(buf));

			write(cltfd, "200 ok\n", strlen("200 ok\n"));
		}
	}

	close(sockfd);
	return 0;
}
