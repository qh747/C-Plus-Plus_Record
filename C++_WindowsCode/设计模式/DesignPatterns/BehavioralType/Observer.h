#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::string;
using std::vector;

// 观察者模式
class AbstractObserver
{
public:
	virtual ~AbstractObserver() {}
	virtual void update(string data) = 0;
};

class PhoneObserver : public AbstractObserver
{
public:
	virtual ~PhoneObserver() {}
	virtual void update(string data) { cout << "Phone Receive: " << data << endl; }
};

class ComputerObserver : public AbstractObserver
{
public:
	virtual ~ComputerObserver() {}
	virtual void update(string data) { cout << "Computer Receive: " << data << endl; }
};

// 观察主题类
class AbstractTopic
{
public:
	virtual ~AbstractTopic() {}
	virtual void subscribe(AbstractObserver* pObserver) = 0;
	virtual void publish(const string& data) = 0;

protected:
	vector<AbstractObserver*> m_observerArray;
};

class NewsTopic : public AbstractTopic
{
public:
	virtual ~NewsTopic() {}
	virtual void subscribe(AbstractObserver* observerPtr);
	virtual void publish(const string& data);
};

// 观察者模式测试函数
void ObserverTestDemo();