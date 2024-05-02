#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// 抽象层
class AbstractLayer
{
public:
	virtual ~AbstractLayer() {}
	virtual string doService(const string& data) = 0;
};

// 底层功能实现层
class ToUpperBottomLayer : public AbstractLayer
{
public:
	virtual ~ToUpperBottomLayer() {}
	virtual string doService(const string& data);
};

class ToLowerBottomLayer : public AbstractLayer
{
public:
	virtual ~ToLowerBottomLayer() {}
	virtual string doService(const string& data);
};

// 上层功能调用层
void DisplayFuncTopLayer(AbstractLayer* pProcMethod, const string& data);

// 依赖倒转原则测试函数
void RelyOnInersionPrincipleTestDemo();
