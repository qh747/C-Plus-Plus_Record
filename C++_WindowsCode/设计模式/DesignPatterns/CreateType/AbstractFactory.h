#pragma once
#include "CreateElement.h"

// 抽象工厂模式
class AbstractFactory
{
public:
	virtual ~AbstractFactory() {}
	virtual AbstractElement* createElement() = 0;
	virtual NewAbstractElement* createNewElement() = 0;
};

class FirstFactory : public AbstractFactory
{
public:
	virtual ~FirstFactory() {}
	virtual AbstractElement* createElement();
	virtual NewAbstractElement* createNewElement();
};

class SecondFactory : public AbstractFactory
{
public:
	virtual ~SecondFactory() {}
	virtual AbstractElement* createElement();
	virtual NewAbstractElement* createNewElement();
};

// 抽象工厂模式测试函数
void AbstractFactoryTestDemo();