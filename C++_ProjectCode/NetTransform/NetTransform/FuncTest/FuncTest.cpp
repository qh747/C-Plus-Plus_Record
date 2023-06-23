#include "FuncTest.h"

/*编解码模块测试							**/
void funcThreadCodecTest()
{
	thread reqCodecThread(funcModelRequestCodecTest);
	thread respCodecThread(funcModelResponseCodecTest);

	reqCodecThread.join();
	respCodecThread.join();
}

void funcModelRequestCodecTest()
{
	/*请求消息初始化						**/
	RequestMsg_dt srcMsg;
	srcMsg.cmdType  = 1;
	srcMsg.clientId = "Client No.1";
	
	srcMsg.serverId = "Server No.1";
	srcMsg.sign     = "Source Message";
	srcMsg.data		= "Register Server";

	Request_Codec reqEncodeModel;
	reqEncodeModel.initMessage(srcMsg);

	cout << "REQUEST SOURCE MSG:" << " " << srcMsg.cmdType << " " << srcMsg.clientId << " " << srcMsg.serverId << " " << srcMsg.sign << " " << srcMsg.data << endl << endl;

	/*请求消息编码							**/
	string encodeMsg = reqEncodeModel.encodeMsg();

	/*请求消息解码							**/
	Request_Codec reqDecodeModel;
	reqDecodeModel.initMessage(encodeMsg);
	RequestMsg_dt* pDstMsg = static_cast<RequestMsg_dt *>(reqDecodeModel.decodeMsg());
	
	cout << "REQUEST DEST MSG:" << " " << pDstMsg->cmdType << " " << pDstMsg->clientId << " " << pDstMsg->serverId << " " << pDstMsg->sign << " " << pDstMsg->data << endl << endl;
	delete pDstMsg;
}

void funcModelResponseCodecTest()
{
	/*响应消息初始化						**/
	ResponseMsg_dt srcMsg;
	srcMsg.clientId = "Client No.1";
	srcMsg.serverId = "Server No.1";
	srcMsg.seckeyId = 1;
	srcMsg.data     = "Register Server";
	srcMsg.status   = true;

	Response_Codec respEncodeModel;
	respEncodeModel.initMessage(srcMsg);

	cout << "RESPONSE SOURCE MSG:" << " " << srcMsg.status << " " << srcMsg.clientId << " " << srcMsg.serverId << " " << srcMsg.seckeyId << " " << srcMsg.data << endl << endl;

	/*响应消息编码							**/
	string encodeMsg = respEncodeModel.encodeMsg();

	/*响应消息解码							**/
	Response_Codec respDecodeModel;
	respDecodeModel.initMessage(encodeMsg);
	ResponseMsg_dt* pDstMsg = static_cast<ResponseMsg_dt *>(respDecodeModel.decodeMsg());

	cout << "RESPONSE DEST MSG:" << " " << pDstMsg->status << " " << pDstMsg->clientId << " " << pDstMsg->serverId << " " << pDstMsg->seckeyId << " " << pDstMsg->data << endl << endl;
	delete pDstMsg;
}


/*Socket模块测试							**/
void funcThreadSocketTest()
{
	thread servThread(funcModelTcpServerTest);
	thread clientThread(funcModelTcpClientTest);

	servThread.join();
	clientThread.join();
}

void funcModelTcpServerTest()
{
	TcpServer serv;
	if (0 != serv.setListen("127.0.0.1", 8001))
		return;

	/*等待客户端连接, 只等待2秒				**/
	TcpSocket* pCommSock = serv.acceptConn(5);
	if (NULL == pCommSock)
		return;
	
	char sendBuf[32] = "Server Has Been Processed Msg.";
	char recvBuf[64] = "\0";
	while (true)
	{
		int recvSize = pCommSock->recvMessage(recvBuf, sizeof(recvBuf), 3);
		if (recvSize > 0)
		{
			/*收到客户端消息				**/
			printf("SERV RECV MSG: %s\n", recvBuf);

			if (0 != strncmp("exit", recvBuf, 4))
			{
				printf("SERV SEND MSG: Server Has Been Processed Msg.\n");
				pCommSock->sendMessage(sendBuf, strlen(sendBuf), 2);
			}
		}
		else
		{
			printf("CLIENT DISCONNECT SERVER.\n");
			break;
		}
		memset(recvBuf, 0, sizeof(recvBuf));
	}
	delete pCommSock;

	printf("SERV EXIT.\n");
	return;
}

void funcModelTcpClientTest()
{
	TcpSocket clientSock;
	if (-1 != clientSock.connectServer("127.0.0.1", 8001, 3))
		printf("CLIENT CONNECT SERVER SUCCESS.\n");
	else
	{
		printf("CLIENT CONNECT SERVER FAILED.\n");
		return;
	}

	char sendBuf[32] = "Client Register Server.";
	printf("CLIENT SEND MSG: Client Register Server.\n");
	clientSock.sendMessage(sendBuf, strlen(sendBuf), 2);

	char recvBuf[64] = "\0";
	clientSock.recvMessage(recvBuf, sizeof(recvBuf), 3);
	printf("CLIENT RECV MSG: %s\n", recvBuf);

	printf("CLIENT EXIT.\n");
	char exitBuf[6] = "exit";
	clientSock.sendMessage(exitBuf, strlen(exitBuf), 2);

	return;
}


/*共享内存模块测试							**/
void funcMemoryShareTest()
{
	thread writeThread(funcModelMemoryShareWriteTest);
	thread readThread(funcModelMemoryShareReadTest);
	thread secReadThread(funcModelMemoryShareReadTest);

	writeThread.join();
	readThread.join();
	secReadThread.join();
}

void funcModelMemoryShareWriteTest()
{
	MemoryShare writeMemory;
	bool allocateResult = writeMemory.allocateMemory(1, "SHARE_MEMORY", 1024, 1);
	if (false == allocateResult)
		return;

	char sendBuf[20] = "hello world.";
	while (true)
	{
		DWORD writeSize = writeMemory.writeData(1, sendBuf, strlen(sendBuf), 0, 1);
		if (0 != writeSize)
		{
			printf("Write Thread Write Data Success. Data: %s. Size: %lu\n", sendBuf, writeSize);
			break;
		}
	}
	
	Sleep(0.5 * 1000);
	while (true)
	{
		bool clearResult = writeMemory.clearMemory(1, 0, strlen(sendBuf), 1);
		if (true == clearResult)
		{
			memset(sendBuf, 0, sizeof(sendBuf));
			strcpy(sendBuf, "hello share memory");
			break;
		}
	}

	while (true)
	{
		DWORD writeSize = writeMemory.writeData(1, sendBuf, strlen(sendBuf), 0, 1);
		if (0 != writeSize)
		{
			printf("Write Thread Write Data Success. Data: %s. Size: %lu\n", sendBuf, writeSize);
			break;
		}
	}
}

void funcModelMemoryShareReadTest()
{
	MemoryShare readMemory;

	char recvBuf[20] = "\0";
	int readCount = 0;
	while (true)
	{
		DWORD readSize = readMemory.readData(1, recvBuf, sizeof(recvBuf), 0, 1);
		if (0 != readSize)
		{
			recvBuf[strlen(recvBuf)] = '\0';
			printf("Read Thread Read Data Success. Data: %s Size: %d\n", recvBuf, strlen(recvBuf));
			++readCount;
		}

		Sleep(1 * 1000);

		if (readCount >= 2)
			break;
	}
}


/*加密模块测试								**/
void funcEncryptTest()
{
	/*MD5加密测试							**/
	Encrypt MD5Encrypt(Encrypt::TYPE_MD5);
	MD5Encrypt.addOriginalData("this is ", strlen("this is "));
	MD5Encrypt.addOriginalData("a test ", strlen("a test "));
	MD5Encrypt.addOriginalData("of MD5.", strlen("of MD5."));

	cout << "SRC DATA: " << "this is a test of MD5." << endl;
	cout << "DST SIZE: " << strlen(MD5Encrypt.getEncryptHexData().c_str()) << endl;
	cout << "DST DATA: " << MD5Encrypt.getEncryptHexData() << endl << endl;

	/*SHA1加密测试							**/
	Encrypt SHA1Encrypt(Encrypt::TYPE_SHA1);
	SHA1Encrypt.addOriginalData("this is ", strlen("this is "));
	SHA1Encrypt.addOriginalData("a test ", strlen("a test "));
	SHA1Encrypt.addOriginalData("of SHA1.", strlen("of SHA1."));

	cout << "SRC DATA: " << "this is a test of SHA1." << endl;
	cout << "DST SIZE: " << strlen(SHA1Encrypt.getEncryptHexData().c_str()) << endl;
	cout << "DST DATA: " << SHA1Encrypt.getEncryptHexData() << endl << endl;

	/*SHA224加密测试						**/
	Encrypt SHA224Encrypt(Encrypt::TYPE_SHA224);
	SHA224Encrypt.addOriginalData("this is ", strlen("this is "));
	SHA224Encrypt.addOriginalData("a test ", strlen("a test "));
	SHA224Encrypt.addOriginalData("of SHA224.", strlen("of SHA224."));

	cout << "SRC DATA: " << "this is a test of SHA224." << endl;
	cout << "DST SIZE: " << strlen(SHA224Encrypt.getEncryptHexData().c_str()) << endl;
	cout << "DST DATA: " << SHA224Encrypt.getEncryptHexData() << endl << endl;

	/*SHA384加密测试						**/
	Encrypt SHA384Encrypt(Encrypt::TYPE_SHA384);
	SHA384Encrypt.addOriginalData("this is ", strlen("this is "));
	SHA384Encrypt.addOriginalData("a test ", strlen("a test "));
	SHA384Encrypt.addOriginalData("of SHA384.", strlen("of SHA384."));

	cout << "SRC DATA: " << "this is a test of SHA384." << endl;
	cout << "DST SIZE: " << strlen(SHA384Encrypt.getEncryptHexData().c_str()) << endl;
	cout << "DST DATA: " << SHA384Encrypt.getEncryptHexData() << endl << endl;
}