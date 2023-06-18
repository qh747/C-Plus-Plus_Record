#include "TcpSocket.h"

TcpSocket::TcpSocket()
{
	/*初始化socket套接字环境			**/
	WSADATA sockEnvir;
	if (0 != WSAStartup(MAKEWORD(2, 2), &sockEnvir))
	{
		std::cerr << "SOCKET ENVIR INIT FAILED. ERR CODE: " << WSAGetLastError() << std::endl;
		return;
	}
		
	/*创建socket						**/
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_sock)
	{
		std::cerr << "SOCKET CREATE FAILED. ERR CODE: " << WSAGetLastError() << std::endl;
		return;
	}
		
	/*设置socket为非阻塞				**/
	unsigned long nonblockflag = 1;
	if (SOCKET_ERROR == ioctlsocket(m_sock, FIONBIO, &nonblockflag))
		std::cerr << "SOCKET SET NONBLOCK FAILED. ERR CODE: " << WSAGetLastError() << std::endl;

	/*设置socket端口复用				**/
	int reuseFlag = 1;
	if (SOCKET_ERROR == setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuseFlag, sizeof(reuseFlag)))
		std::cerr << "TCP SERVER SET REUSE ADDR FAILED. ERR CODE: " << WSAGetLastError() << std::endl;
}

TcpSocket::~TcpSocket()
{
	/*关闭socket						**/
	closesocket(m_sock);

	/*socket套接字环境清理				**/
	WSACleanup();
}

TcpSocket::TcpSocket(SOCKET servSock)
{
	if (INVALID_SOCKET == servSock)
		std::cerr << "SOCKET ASSIGN FAILED." << std::endl;
	else
		m_sock = servSock;
}

int	TcpSocket::connectServer(const string& ip, unsigned short port, unsigned long timeout)
{
	/*函数入参有效性检查							**/
	if (true == ip.empty() || port <= 0 || timeout <= 0)
	{
		std::cout << "FUNC INPUT PARAM ERROR, FUNC NAME: connectServer() " << std::endl;
		return -1;
	}

	/*服务端地址信息创建							**/
	sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	servAddr.sin_port = port;

	/*服务端连接									**/
	int connResult = 0;
	/*非阻塞状态下连接会立即返回					**/
	connResult = connect(m_sock, (sockaddr *)&servAddr, sizeof(servAddr));
	if (0 != connResult)
	{
		/*select设置								**/
		fd_set sendSet;
		FD_ZERO(&sendSet);
		FD_SET(m_sock, &sendSet);

		/*通过select判断连接是否成功				**/
		timeval sendTimeOut = { timeout, 0 };
		int selectResult = select(m_sock + 1, NULL, &sendSet, NULL, &sendTimeOut);
		if (0 == selectResult)
		{
			/*连接超时								**/
			std::cout << "SOCKET CONNECT TCP SERVER TIMEOUT." << std::endl;
			return -1;
		}
		else if (-1 == selectResult)
		{
			/*连接失败								**/
			std::cout << "SOCKET CONNECT TCP SERVER ERROR 1. ERROR CODE: " << WSAGetLastError() << std::endl;
			return -1;
		}
		else
		{
			/*获取socket属性，判断连接是否成功		**/
			int connError = 0;
			int errorLen = sizeof(connError);
			if (getsockopt(m_sock, SOL_SOCKET, SO_ERROR, (char *)&connError, &errorLen) < 0)
			{
				std::cout << "SOCKET CONNECT TCP SERVER ERROR 2. ERROR CODE: " << WSAGetLastError() << std::endl;
				return -1;
			}

			if (0 != connError)
			{
				std::cout << "SOCKET CONNECT TCP SERVER ERROR 3. ERROR CODE: " << connError << std::endl;
				return -1;
			}

			/*连接成功								**/
			return 0;
		}
	}
	else
		return 0;
}

int TcpSocket::sendMessage(void* pMsgBody, int msgBodySize, unsigned long timeout)
{
	/*函数入参有效性检查											**/
	if (NULL == pMsgBody || msgBodySize <= 0 || timeout <= 0)
	{
		std::cout << "FUNC INPUT PARAM ERROR, FUNC NAME: sendMessage() " << std::endl;
		return -1;
	}

	/*判断是否能发送消息											**/
	bool canSendMsg = this->canSendMessage(timeout);
	if (false == canSendMsg)
		return -1;

	/*消息首部为int类型数据，需要由主机字节序转换为网络字节序		**/
	int msgHead = htonl(msgBodySize);				
	int msgSize = msgBodySize + sizeof(int);

	/*消息内容填充													**/
	char* pStrBuf = new char[msgSize];
	memcpy(pStrBuf, &msgHead, sizeof(int));
	memcpy(pStrBuf + sizeof(int), pMsgBody, msgBodySize);

	/*消息发送														**/
	int sendSize = this->sendBytes(pStrBuf, msgSize);
	delete[] pStrBuf;

	return sendSize;
}

int TcpSocket::recvMessage(void* pMsgBody, int msgBodySize, unsigned long timeout)
{
	/*函数入参有效性检查								**/
	if (NULL == pMsgBody || msgBodySize <= 0 || timeout <= 0)
	{
		std::cout << "FUNC INPUT PARAM ERROR, FUNC NAME: recvMessage() " << std::endl;
		return -1;
	}

	/*判断是否能接收消息								**/
	bool canRecvMsg = this->canRecvMessage(timeout);
	if (false == canRecvMsg)
		return -1;

	/*判断接收缓冲区是否有数据							**/
	unsigned long hasData = 0;
	ioctlsocket(m_sock, FIONREAD, &hasData);			// 用于非阻塞模式下判断对端是否断开连接
	if (hasData <= 0)
		return 0;

	/*接收消息首部										**/
	int msgHead = 0;
	this->recvBytes(&msgHead, sizeof(msgHead));

	/*获取消息的实际长度								**/
	int msgSize = ntohl(msgHead);
	if (msgSize <= 0)
		return msgSize;									// 对端断开连接
	
	/*接收消息内容										**/
	char* pStrBuf = static_cast<char *>(pMsgBody);
	if (msgSize <= msgBodySize)
	{
		/*消息长度小于等于接收缓冲区长度				**/
		this->recvBytes(pStrBuf, msgSize);
		pStrBuf[msgSize] = '\0';
		return msgSize;
	}
	else
	{
		/*消息长度大于接收缓冲区长度					**/
		char* pTmpBuf = new char[msgSize];
		this->recvBytes(pTmpBuf, msgSize);

		memcpy(pStrBuf, pTmpBuf, msgBodySize);
		pStrBuf[msgBodySize] = '\0';

		delete[] pTmpBuf;
		return msgBodySize;
	}
}

bool TcpSocket::canRecvMessage(unsigned long timeout)
{
	/*select设置						**/
	fd_set recvSet;
	FD_ZERO(&recvSet);
	FD_SET(m_sock, &recvSet);

	timeval readTimeOut = { timeout, 0 };
	int selectResult = select(m_sock + 1, &recvSet, NULL, NULL, &readTimeOut);

	if (selectResult < 0)
		return false;
	else if (0 == selectResult)
		return false;

	if (m_sock != recvSet.fd_array[0])
		return false;
	else
		return true;
}

bool TcpSocket::canSendMessage(unsigned long timeout)
{
	/*select设置						**/
	fd_set sendSet;
	FD_ZERO(&sendSet);
	FD_SET(m_sock, &sendSet);

	timeval sendTimeOut = { timeout, 0 };
	int selectResult = select(m_sock + 1, NULL, &sendSet, NULL, &sendTimeOut);
	if (selectResult < 0)
		return false;
	else if (0 == selectResult)
		return false;

	if (m_sock != sendSet.fd_array[0])
		return false;
	else
		return true;
}

int TcpSocket::recvBytes(void* pRecvBuf, int recvSize)
{
	int curRecvSize = 0;
	char* pStrBuf = static_cast<char *>(pRecvBuf);
	while (curRecvSize < recvSize)
	{
		curRecvSize += recv(m_sock, pStrBuf + curRecvSize, (recvSize - curRecvSize), 0);
	}

	return curRecvSize;
}

int TcpSocket::sendBytes(void* pSendBuf, int sendSize)
{
	int curSendSize = 0;
	char* pStrBuf = static_cast<char *>(pSendBuf);
	while (curSendSize < sendSize)
	{
		curSendSize += send(m_sock, pStrBuf + curSendSize, (sendSize - curSendSize), 0);
	}

	return curSendSize;
}