#pragma once
#include <queue>
#include <string>
#include <iostream>
using std::queue;
using std::string;
using std::cerr;
using std::endl;

/*单调队列									**/
class BasicMonotonicQueue
{
public:
	virtual ~BasicMonotonicQueue() {}

public:
	virtual void	push(int val) = 0;					// 插入元素
	virtual void	pop() = 0;							// 弹出元素
	virtual int		top() = 0;							// 获取队首元素
	virtual bool    empty() { return m_que.empty(); }	// 判断队列是否为空

protected:
	queue<int> m_que;
};

/*单调递增队列								**/
class IncreaseMonotonicQueue : public BasicMonotonicQueue
{
public:
	virtual ~IncreaseMonotonicQueue() {}

public:
	virtual void	push(int val);
	virtual void	pop();
	virtual int		top();
};

/*单调递减队列								**/
class DecreaseMonotonicQueue : public BasicMonotonicQueue
{
public:
	virtual ~DecreaseMonotonicQueue() {}

public:
	virtual void	push(int val);
	virtual void	pop();
	virtual int		top();
};