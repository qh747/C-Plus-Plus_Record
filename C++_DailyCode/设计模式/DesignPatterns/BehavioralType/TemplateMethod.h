#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// 模板方法模式
class AbstractMethod
{
public:
	virtual ~AbstractMethod() {}

	// 基类在processMsg()函数定义recvMsg()、praseMsg()、sendMsg()函数的执行顺序
	virtual string processMsg(const string& msg);

protected:
	virtual void recvMsg(const string& msg) = 0;
	virtual void praseMsg() = 0;
	virtual const string& sendMsg() = 0;

protected:
	string m_msg;
};

class FastProcessMethod : public AbstractMethod
{
public:
	virtual ~FastProcessMethod() {}

protected:
	// 派生类实现函数细节
	virtual void recvMsg(const string& msg);
	virtual void praseMsg();
	virtual const string& sendMsg();
};

class SafeProcessMethod : public AbstractMethod
{
public:
	virtual ~SafeProcessMethod() {}

protected:
	// 派生类实现函数细节
	virtual void recvMsg(const string& msg);
	virtual void praseMsg();
	virtual const string& sendMsg();
};

// 模板方法模式测试函数
void TemplateMethodTestDemo();