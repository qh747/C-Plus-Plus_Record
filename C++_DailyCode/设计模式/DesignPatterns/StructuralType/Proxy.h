#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// 被代理类
class AbstractServer
{
public:
	virtual ~AbstractServer() {}
	virtual void startServer() = 0;
};

class HttpServer : public AbstractServer
{
public:
	virtual ~HttpServer() {}

public:
	virtual void startServer() { cout << "Http Server Start." << endl; }
};

// 代理模式
class ServerProxy : public AbstractServer
{
public:
	ServerProxy(string userName, string userPasswd) : m_userName(userName), m_userPasswd(userPasswd), m_pServer(new HttpServer()) {}
	virtual ~ServerProxy();
	virtual void startServer();

private:
	string				m_userName;
	string				m_userPasswd;
	AbstractServer*		m_pServer;
};

// 代理模式测试函数
void ProxyTestDemo();