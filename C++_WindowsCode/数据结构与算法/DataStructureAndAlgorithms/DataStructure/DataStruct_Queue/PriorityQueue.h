#pragma once
#include <vector>
#include <string>
#include <iostream>
using std::vector;
using std::string;
using std::cerr;
using std::endl;
using std::swap;

// 优先队列基类
class BasicPriorityQueue
{
public:
	virtual ~BasicPriorityQueue() {}

public:
	virtual void push(int val) = 0;
	virtual int  top() = 0;
	virtual void pop() = 0;
	virtual bool empty() { return m_queue.empty(); }

protected:
	virtual void adjust() = 0;

protected:
	vector<int> m_queue;
};

// 优先队列 - 大顶堆
class BigTopPriorityQueue : public BasicPriorityQueue
{
public:
	virtual ~BigTopPriorityQueue() {}

public:
	virtual void push(int val);
	virtual int  top();
	virtual void pop();

protected:
	virtual void adjust();
};

// 优先队列 - 小顶堆
class SmallTopPriorityQueue : public BasicPriorityQueue
{
public:
	virtual ~SmallTopPriorityQueue() {}

public:
	virtual void push(int val);
	virtual int  top();
	virtual void pop();

protected:
	virtual void adjust();
};