#include "Proxy.h"

ServerProxy::~ServerProxy()
{
	if (NULL == m_pServer)
		return;

	delete m_pServer;
	m_pServer = NULL;
}

void ServerProxy::startServer()
{
	// 代理函数, 增加登录验证功能
	if ("admin" == m_userName && "123456"  == m_userPasswd)
	{
		cout << "Authenticate Success. Server Is Starting." << endl;
		m_pServer->startServer();
	}
	else
		cout << "Login Info Error." << endl;
}

void ProxyTestDemo()
{
	AbstractServer* pServer = new ServerProxy(string("admin"), string("123456"));
	pServer->startServer();

	delete pServer;
}