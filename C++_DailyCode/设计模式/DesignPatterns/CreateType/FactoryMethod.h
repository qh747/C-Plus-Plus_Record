#pragma once
#include "CreateElement.h"

// 工厂方法模式
class AbstractFactoryMethod
{
public:
	virtual ~AbstractFactoryMethod() {}
	virtual AbstractElement* createElement() = 0;
};

class FristFactoryMethod : public AbstractFactoryMethod
{
public:
	virtual ~FristFactoryMethod() {}
	virtual AbstractElement* createElement();
};

class SecondFactoryMethod : public AbstractFactoryMethod
{
public:
	virtual ~SecondFactoryMethod() {}
	virtual AbstractElement* createElement();
};

// 工厂方法模式测试函数
void FactoryMethodTestDemo();