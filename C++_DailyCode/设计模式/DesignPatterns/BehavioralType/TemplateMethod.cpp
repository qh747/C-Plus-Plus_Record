#include "TemplateMethod.h"

string AbstractMethod::processMsg(const string& msg)
{
	this->recvMsg(msg);
	this->praseMsg();
	return this->sendMsg();
}

void FastProcessMethod::recvMsg(const string& msg)
{
	cout << "Fast Recv: " << msg << endl;
	m_msg = msg;
}

void FastProcessMethod::praseMsg()
{
	cout << "Fast Prase: " << m_msg << endl;
}

const string& FastProcessMethod::sendMsg()
{
	cout << "Fast Send: " << m_msg << endl;
	return m_msg;
}

void SafeProcessMethod::recvMsg(const string& msg)
{
	cout << "Safe Recv: " << msg << endl;
	m_msg = msg;
}

void SafeProcessMethod::praseMsg()
{
	cout << "Safe Prase: " << m_msg << endl;
}

const string& SafeProcessMethod::sendMsg()
{
	cout << "Safe Send: " << m_msg << endl;
	return m_msg;
}

void TemplateMethodTestDemo()
{
	string srcMsg = "Hello";
	AbstractMethod* pFastMsgMethod = new FastProcessMethod();
	string fastProcMsg = pFastMsgMethod->processMsg(srcMsg);
	cout << fastProcMsg << endl;

	AbstractMethod* pSafeMsgMethod = new SafeProcessMethod();
	string safeProcMsg = pSafeMsgMethod->processMsg(srcMsg);
	cout << safeProcMsg << endl;

	delete pFastMsgMethod;
	delete pSafeMsgMethod;
}