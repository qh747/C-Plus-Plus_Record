#include "TcpServer.h"

TcpServer::TcpServer()
{
	/*初始化socket套接字环境			**/
	WSADATA sockEnvir;
	if (0 != WSAStartup(MAKEWORD(2, 2), &sockEnvir))
	{
		std::cerr << "TCP SERVER ENVIR INIT FAILED. ERR CODE: " << WSAGetLastError() << std::endl;
		return;
	}

	/*创建socket						**/
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_sock)
	{
		std::cerr << "TCP SERVER CREATE FAILED. ERR CODE: " << WSAGetLastError() << std::endl;
		return;
	}
		
	/*设置socket为非阻塞				**/
	unsigned long nonblockflag = 1;
	if (SOCKET_ERROR == ioctlsocket(m_sock, FIONBIO, &nonblockflag))
		std::cerr << "TCP SERVER SET NONBLOCK FAILED. ERR CODE: " << WSAGetLastError() << std::endl;

	/*设置socket端口复用				**/
	int reuseFlag = 1;
	if(SOCKET_ERROR == setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuseFlag, sizeof(reuseFlag)))
		std::cerr << "TCP SERVER SET REUSE ADDR FAILED. ERR CODE: " << WSAGetLastError() << std::endl;
}

TcpServer::~TcpServer()
{
	/*关闭socket						**/
	closesocket(m_sock);

	/*socket套接字环境清理				**/
	WSACleanup();
}

int TcpServer::setListen(const string& ip, unsigned short port)
{
	/*服务端地址信息创建				**/
	sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	servAddr.sin_port = port;

	/*服务端地址信息绑定				**/
	if (SOCKET_ERROR == bind(m_sock, (sockaddr *)&servAddr, sizeof(servAddr)))
	{
		std::cerr << "TCP SERVER BIND FAILED. ERR CODE: " << WSAGetLastError() << std::endl;
		return -1;
	}
		
	/*服务端地址信息监听				**/
	if (SOCKET_ERROR == listen(m_sock, 1024))
	{
		std::cerr << "TCP SERVER LISTEN FAILED. ERR CODE: " << WSAGetLastError() << std::endl;
		return -1;
	}
		
	return 0;
}

TcpSocket* TcpServer::acceptConn(unsigned long timeout)
{
	sockaddr_in commAddr;
	int addrlen = sizeof(commAddr);
	memset(&commAddr, 0, addrlen);

	/*通过select判断客户端是否发起连接	**/
	fd_set connSet;
	FD_ZERO(&connSet);
	FD_SET(m_sock, &connSet);

	timeval waitTime = {3, 0};
	int selectResult = select(m_sock + 1, &connSet, NULL, NULL, &waitTime);
	if (0 == selectResult || m_sock != connSet.fd_array[0])
	{
		/*等待客户端连接超时			**/
		std::cout << "WAIT CLIENT CONNECT TIME OUT." << std::endl;
		return NULL;
	}
	
	/*客户端在指定时间内连接成功		**/
	SOCKET commSock = accept(m_sock, (sockaddr *)&commAddr, &addrlen);
	if (INVALID_SOCKET == commSock)
	{
		std::cerr << "TCP SERVER ACCEPT FAILED. ERR CODE: " << WSAGetLastError() << std::endl;
		return NULL;
	}

	TcpSocket* pCommSock = new TcpSocket(commSock);
	return pCommSock;
}