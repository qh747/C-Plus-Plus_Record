#pragma once
#include <iostream>
using std::cout;
using std::endl;

// 开闭原则
class AbstractOperator
{
public:
	virtual ~AbstractOperator() {}
	virtual int doOperate(int lft, int rght) = 0;
};

class AddOperator : public AbstractOperator
{
public:
	virtual ~AddOperator() {}
	virtual int doOperate(int lft, int rght) { return lft + rght; }
};

class ReduceOperator : public AbstractOperator
{
public:
	virtual ~ReduceOperator() {}
	virtual int doOperate(int lft, int rght) { return lft - rght; }
};

// 开闭原则测试函数
void OpenClosePrincipleTestDemo();