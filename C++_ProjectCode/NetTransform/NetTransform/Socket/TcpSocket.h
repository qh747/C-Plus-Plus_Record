#pragma once
#pragma warning(disable: 4996)
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <ctime>
#include <cstdlib>
using std::string;

/*TCP套接字，用于服务端与客户端通信，支持服务端、客户端使用									**/
class TcpSocket
{
public:
	TcpSocket();																			// TCP客户端使用，构造函数
	~TcpSocket();																			// 析构函数
	TcpSocket(SOCKET servSock);																// TCP服务端使用，构造函数

public:
	int		connectServer(const string& ip, unsigned short port, unsigned long timeout);	// TCP客户端使用，连接TCP服务端
	int 	sendMessage(void* pMsgBody, int msgBodySize, unsigned long timeout);			// 发送消息
	int		recvMessage(void* pMsgBody, int msgBodySize, unsigned long timeout);			// 接收消息

private:
	bool    canRecvMessage(unsigned long timeout);											// 指定时间内是否能接收消息判断
	bool    canSendMessage(unsigned long timeout);											// 指定时间内是否能发送消息判断

	int		recvBytes(void* pRecvBuf, int recvSize);										// 接收n字节数据
	int		sendBytes(void* pSendBuf, int sendSize);										// 发送n字节数据

	bool	isSockValid();																	// 判断socket是否有效

private:
	SOCKET m_sock;																			// socket通信套接字
};