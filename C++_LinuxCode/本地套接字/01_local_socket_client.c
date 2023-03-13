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
	struct sockaddr_un cltAddr;
	cltAddr.sun_family = AF_UNIX;
	strcpy(cltAddr.sun_path, "socket.client");

	socklen_t addrLen = sizeof(cltAddr);

	/*取消之前创建的文件	**/
	unlink("socket.client");
	int bindRet = bind(sockfd, (struct sockaddr *)&cltAddr, addrLen);
	if(-1 == bindRet)
	{
		perror("bind() error");
		close(sockfd);

		return -1;
	}

	/*与服务端建立连接		**/
	struct sockaddr_un servAddr;
	servAddr.sun_family = AF_UNIX;
	strcpy(servAddr.sun_path, "socket.serv");

	int connectRet = connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr));
	if(-1 == connectRet)
	{
		perror("connect() error");
		close(sockfd);

		return -1;
	}
	
	/*与服务端通信			**/
	char buf[64] = "\0";
	memset(buf, 0, sizeof(buf));
	
	while(true)
	{
		printf("input(enter q to quit): ");
		fgets(buf, sizeof(buf), stdin);

		if(0 == strncmp("q", buf, 1))
		{
			printf("client exit\n");
			break;
		}
		else
		{
			write(sockfd, buf, strlen(buf));
			memset(buf, 0, sizeof(buf));

			int recvSize = read(sockfd, buf, sizeof(buf));
        	if(recvSize < 0)
        	{
        	    perror("read() error");
        	    break;
       		}
        	else if(0 == recvSize)
        	{
        	    printf("server exit\n");
        	    break;
        	}
        	else
        	{
        	    printf("client recv: %s", buf);
				memset(buf, 0, sizeof(buf));
			}
		}
	}

	close(sockfd);
	return 0;
}
