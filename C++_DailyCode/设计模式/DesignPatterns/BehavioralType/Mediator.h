#pragma once
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

class AbstractMediator;

// 抽象同事类 
class AbstractColleague
{
public:
	void	setMediator(AbstractMediator* pMedaitor) { m_pMediator = pMedaitor; }
	virtual ~AbstractColleague() {}
	virtual void sendMsg(string msg) = 0;
	virtual void recvMsg(string msg) = 0;

protected:
	AbstractMediator*  m_pMediator;
};

// 抽象中介者类
class AbstractMediator
{
public:
	virtual ~AbstractMediator() {}
	virtual void addColl(AbstractColleague* coll) = 0;
	virtual void relayMsg(string msg) = 0;
};

// 功能同事类
class FuncCollegue : public AbstractColleague
{
public:
	virtual ~FuncCollegue() {}
	virtual void sendMsg(string msg);
	virtual void recvMsg(string msg);
};

// 界面同事类
class DisplayCollegue : public AbstractColleague
{
public:
	virtual ~DisplayCollegue() {}
	virtual void sendMsg(string msg);
	virtual void recvMsg(string msg);
};

// 功能中介者类
class FuncMediator : public AbstractMediator
{
public:
	virtual ~FuncMediator() {}
	virtual void addColl(AbstractColleague* aoll);
	virtual void relayMsg(string msg);

private:
	vector<AbstractColleague*> m_collVec;
};

// 界面中介者类
class DisplayMediator : public AbstractMediator
{
public:
	virtual ~DisplayMediator() {}
	virtual void addColl(AbstractColleague* aoll);
	virtual void relayMsg(string msg);

private:
	vector<AbstractColleague*> m_collVec;
};

// 中介者模式测试函数
void MediatorTestDemo();