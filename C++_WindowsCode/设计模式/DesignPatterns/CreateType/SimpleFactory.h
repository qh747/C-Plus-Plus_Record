#pragma once
#include "CreateElement.h"

// 简单工厂模式
class SimpleFactory
{
public:
	static AbstractElement* createElement(const string& name);
};

// 简单工厂模式测试函数
void SimpleFactoryTestDemo();	