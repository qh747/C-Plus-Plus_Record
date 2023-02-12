#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/wait.h>

/*全局变量	**/
int GLOBAL_TCP_SERVER_SOCKET = 0;

/*信号处理函数	**/
void signal_processFunc(int sig)
{
	if(SIGINT == sig)
	{
		close(GLOBAL_TCP_SERVER_SOCKET);
		raise(SIGTERM);
	}
	else if(SIGCHLD == sig)
	{
		pid_t pid;
		while(true)
		{
			pid = waitpid(-1, NULL, WNOHANG);
			if(pid <= 0)
				break;
		}
	}
	
	return;
}


int main()
{
	/*创建TCP SERVER套接字	**/
	GLOBAL_TCP_SERVER_SOCKET = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(-1 == GLOBAL_TCP_SERVER_SOCKET)
	{
		perror("socket() error");
		return -1;
	}

	/*绑定本机IP地址	**/
	struct sockaddr_in serverIpAddr;
	memset(&serverIpAddr, 0, sizeof(serverIpAddr));

	serverIpAddr.sin_family = AF_INET;
	serverIpAddr.sin_port = htons(8000);
	serverIpAddr.sin_addr.s_addr = inet_addr("192.168.0.188");

	int bindRet = bind(GLOBAL_TCP_SERVER_SOCKET, (struct sockaddr*)&serverIpAddr, sizeof(serverIpAddr));
   	if(-1 == bindRet)
	{
		perror("bind() error");

		close(GLOBAL_TCP_SERVER_SOCKET);
		return -1;
	}	

	/*监听客户端连接, 16表示允许客户端的最大接入数量	**/
	int listenRet = listen(GLOBAL_TCP_SERVER_SOCKET, 16);
	if(-1 == listenRet)
	{
		perror("listen() error");

		close(GLOBAL_TCP_SERVER_SOCKET);
		return -1;
	}

	/*阻塞子进程退出信号	**/
	sigset_t blockSet;
	sigemptyset(&blockSet);

	sigaddset(&blockSet, SIGCHLD);
	sigprocmask(SIG_BLOCK, &blockSet, NULL);

	/*接受客户端的连接	**/
	while(true)
	{
		/*获取客户端的IP地址和端口信息	**/
		struct sockaddr_in clientIpAddr;
		memset(&clientIpAddr, 0, sizeof(clientIpAddr));

		socklen_t ipAddrLength = sizeof(clientIpAddr);
	
		/*等待客户端接入	**/
		int clientSocket = accept(GLOBAL_TCP_SERVER_SOCKET, (struct sockaddr*)&clientIpAddr, &ipAddrLength);
		if(-1 == clientSocket)
		{
			if((ECONNABORTED == errno) || (EINTR == errno))
			{
				/*防止被外部信号打断	**/
				continue;
			}
			else
				break;
		}
	
		/*打印客户端信息	**/
		char ipAddr[16] = "\0";
		inet_ntop(AF_INET, &clientIpAddr.sin_addr, ipAddr, INET_ADDRSTRLEN);

		int port = ntohs(clientIpAddr.sin_port);

		printf("new client connect. ip: %s port: %d\n", ipAddr, port);

		/*创建子进程与客户端通信	**/
		pid_t childId = fork();
		if(-1 == childId)
		{
			perror("fork() error");
			
			close(clientSocket);
			continue;
		}
		else if(0 == childId)
		{
			/*关闭从父进程继承的监听套接字	**/
			close(GLOBAL_TCP_SERVER_SOCKET);

			/*子进程	**/
			char recvBuf[64] = "\0";
			memset(recvBuf, 0, sizeof(recvBuf));
				
			while(true)
			{
				int readRet = read(clientSocket, recvBuf, sizeof(recvBuf));
				if(readRet < 0)
				{
					/*数据读取错误	**/
					printf("recv client data error. ip: %s port: %d\n", ipAddr, port);

					close(clientSocket);
					exit(0);
				}
				else if(0 == readRet)
				{
					/*客户端退出	**/
					printf("client disconnect. ip: %s port: %d\n", ipAddr, port);

					close(clientSocket);
					exit(0);
				}
				else
				{
					printf("recv client data. ip: %s port: %d data: %s", ipAddr, port, recvBuf);

					/*返回客户端确认消息	**/
					char sendBuf[10] = "200 ok\n";
					write(clientSocket, sendBuf, sizeof(sendBuf));
				}

				/*一轮消息交互完成后清除本轮缓存	**/
				memset(recvBuf, 0, sizeof(recvBuf));
			}
		}
		else
		{
			/*关闭与客户端通信的套接字, 父进程只负责接受新客户端连接	**/
			close(clientSocket);

			/*父进程	**/
			sigprocmask(SIG_UNBLOCK, &blockSet, NULL);

			/*注册子进程退出信号处理函数	**/
			signal(SIGCHLD, signal_processFunc);
			signal(SIGINT, signal_processFunc);	
		}
	}

	/*本进程意外退出回收socket资源	**/
	close(GLOBAL_TCP_SERVER_SOCKET);
	return 0;
}
