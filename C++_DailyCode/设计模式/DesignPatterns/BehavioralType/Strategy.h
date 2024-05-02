#pragma once
#include <iostream>
using std::cout;
using std::endl;

// 策略模式
class AbstractStrategy
{
public:
	AbstractStrategy() {}
	virtual ~AbstractStrategy() {}

public:
	virtual double doOperate(double fstVale, double lstVal) = 0;
};

class AddStrategy : public AbstractStrategy
{
public:
	virtual ~AddStrategy() {}
	virtual double doOperate(double fstVale, double lstVal) { return fstVale + lstVal; }
};

class ReduceStrategy : public AbstractStrategy
{
public:
	virtual ~ReduceStrategy() {}
	virtual double doOperate(double fstVale, double lstVal) { return fstVale - lstVal; }
};

// 策略使用类
class ContextClass
{
public:
	ContextClass(AbstractStrategy* pStrategy) { m_pStrategy = pStrategy; }
	~ContextClass() {}

public:
	void setStrategy(AbstractStrategy* pStrategy) { m_pStrategy = pStrategy; }
	double doOperate(double fstVal, double lstVal) { return m_pStrategy->doOperate(fstVal, lstVal); }

private:
	AbstractStrategy* m_pStrategy;
};

// 策略模式测试函数
void StrategyTestDemo();