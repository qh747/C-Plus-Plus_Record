#include <iostream>
#include <cstring>
#include <string>
using namespace std;

/*接收类，服务器类    **/
class ServerClass
{
public:
	void dataOperate()
	{
		cout << "Server Receive Data. Storage Data." << endl;
	}

	void messageOperate()
	{
		cout << "Server Receive Message. Process Message." << endl;
	}

	void commandOperate()
	{
		cout << "Server Receive Command. Response Command." << endl;
	}
};

/*命令类    **/
class AbstractOperateClass
{
public:
	virtual ~AbstractOperateClass() { }

public:
	virtual void operate() = 0;
};

class DataOperateClass : public AbstractOperateClass
{
public:
	DataOperateClass(ServerClass* pServer) : m_pServer(pServer) { }
	virtual ~DataOperateClass() { }

public:
	virtual void operate()
	{
		if (NULL == m_pServer)
			return;

		m_pServer->dataOperate();
	}

private:
	ServerClass* m_pServer;
};

class MessageOperateClass : public AbstractOperateClass
{
public:
	MessageOperateClass(ServerClass* pServer) : m_pServer(pServer) { }
	virtual ~MessageOperateClass() { }

public:
	virtual void operate()
	{
		if (NULL == m_pServer)
			return;

		m_pServer->messageOperate();
	}

private:
	ServerClass* m_pServer;
};

class CommandOperateClass : public AbstractOperateClass
{
public:
	CommandOperateClass(ServerClass* pServer) : m_pServer(pServer) { }
	virtual ~CommandOperateClass() { }

public:
	virtual void operate()
	{
		if (NULL == m_pServer)
			return;

		m_pServer->commandOperate();
	}

private:
	ServerClass* m_pServer;
};

/*发送类，客户端类    **/
class ClientClass
{
public:
	void setOperate(AbstractOperateClass* pOperate)
	{
		m_pOperate = pOperate;
	}

	void execute()
	{
		if (NULL == m_pOperate)
			return;

		m_pOperate->operate();
	}

private:
	AbstractOperateClass* m_pOperate;
};


int main()
{
	/*创建接收者和发送者    **/
	ServerClass* serverPtr = new ServerClass();
	ClientClass* clientPtr = new ClientClass();

	/*执行发送数据操作    **/
	AbstractOperateClass* operatePtr = new DataOperateClass(serverPtr);
	clientPtr->setOperate(operatePtr);
	cout << "Client Send Data." << endl;
	clientPtr->execute();

	/*执行发送消息操作    **/
	delete operatePtr;
	operatePtr = new MessageOperateClass(serverPtr);
	clientPtr->setOperate(operatePtr);
	cout << "Client Send Message." << endl;
	clientPtr->execute();

	/*执行发送命令操作    **/
	delete operatePtr;
	operatePtr = new CommandOperateClass(serverPtr);
	clientPtr->setOperate(operatePtr);
	cout << "Client Send Command." << endl;
	clientPtr->execute();

	delete clientPtr;
	clientPtr = NULL;

	delete serverPtr;
	serverPtr = NULL;

	system("pause");
	return 0;
}