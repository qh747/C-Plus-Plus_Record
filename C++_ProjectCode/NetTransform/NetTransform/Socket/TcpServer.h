#pragma once 
#include "TcpSocket.h"
/*TCP 服务端															**/
class TcpServer
{
public:
	TcpServer();
	~TcpServer();

public:
	int			setListen(const string& ip, unsigned short port);		// 设置TCP服务端监听的IP地址和端口
	TcpSocket*	acceptConn(unsigned long timeout);						// 等待客户端连接，通过timeout参数设置等待时长

private:
	SOCKET		m_sock;													// TCP服务端使用套接字
};