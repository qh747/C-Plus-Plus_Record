#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

/*TCP服务端函数    **/
int tcpServerFunc();

int main()
{
    int tcp_server_func_ret = tcpServerFunc();

    return 0;
}

int tcpServerFunc()
{
    /*创建TCP Socket    **/
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sockfd)
    {
        perror("socket() error");
        return -1;
    }

    /*绑定IP和端口号    **/
    struct sockaddr_in ipAddr;
    memset(&ipAddr, 0, sizeof(ipAddr));
	
	ipAddr.sin_family = AF_INET;
    ipAddr.sin_port = htons(1027);
	ipAddr.sin_addr.s_addr = inet_addr("192.168.0.188");

    int bind_ret = bind(sockfd, (struct sockaddr *)&ipAddr, sizeof(ipAddr));
	if(-1 == bind_ret)
	{
		perror("bind() error");
		return -1;
	}

	/*监听客户端连接   **/
	int listen_ret = listen(sockfd, 4);
	if(-1 == listen_ret)
	{
		perror("listen() error");
		return -1;
	}

	/*接受客户端的连接    **/
	struct sockaddr_in clientIpAddr;
	memset(&clientIpAddr, 0, sizeof(struct sockaddr_in));

	socklen_t clientIpAddrLength = 0;

	int trans_sockfd = accept(sockfd, (struct sockaddr *)&clientIpAddr, &clientIpAddrLength);
	if(-1 == trans_sockfd)
	{
		perror("accept() error");
		return -1;
	}

    /*与TCP Server通信    **/
    char sendBuf[64] = "\0";
	char recvBuf[64] = "\0";

    while(true)
    {
		/*阻塞并等待客户端发送数据    **/
        int recvSize = read(trans_sockfd, recvBuf, sizeof(recvBuf));

		if(0 == strncmp("quit", recvBuf, 4))
		{
			printf("server quit because client disconnect\n");
			break;
		}
		else
			printf("server recv size:%d recv: %s\n", recvSize, recvBuf);
	
        /*捕获用户输入数据, 使用fgets()函数会捕获到换行符, 因此输出时不需要在末尾加\n    **/
		printf("input: ");
        fgets(sendBuf, sizeof(sendBuf), stdin);

        /*发送数据     **/
		int sendBufSize = strlen(sendBuf);
        int sendSize = write(trans_sockfd, sendBuf, sendBufSize);
		printf("server buf size: %d send size: %d send: %s", sendBufSize, sendSize, sendBuf);

        /*清空本次通信缓存    **/
        memset(sendBuf, 0, sizeof(sendBuf));
		memset(recvBuf, 0, sizeof(recvBuf));
    }

    /*关闭TCP Socket    **/
	close(trans_sockfd);
	close(sockfd);

    return 0;
}

