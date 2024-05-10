#pragma once
#include <iostream>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

// 需要适配的类
class CalculateClass
{
public:		
	virtual ~CalculateClass() {}
	virtual int addValue(int fstVal, int secVal) { return fstVal + secVal; }
};

class ShowValueClass
{
public:
	virtual void showValue(const string& val) { cout << "Val: " << val << endl; }
};

// 对象适配器模式
class CalculateClassAdapter : public CalculateClass, public ShowValueClass
{
public:		
	virtual ~CalculateClassAdapter() {}
	virtual int  addValue(int val) { return this->CalculateClass::addValue(val, 0); }
	virtual int  addValue(int fstVal, int secVal, int thrVal) { return this->CalculateClass::addValue(fstVal, secVal + thrVal); }
	virtual void showValue(const int val);
};

// 类适配器模式
class CalculateObjAdapter : public CalculateClass
{
public:
	virtual ~CalculateObjAdapter() {}
	virtual int  addValue(int val) { return this->CalculateClass::addValue(val, 0); }
	virtual int  addValue(int fstVal, int secVal, int thrVal) { return this->CalculateClass::addValue(fstVal, secVal + thrVal); }
	virtual void showValue(const int val);

private:
	ShowValueClass m_showValue;
};

// 类适配器模式测试函数
void ClassAdapterTestDemo();

// 对象适配器模式测试函数
void ObjAdapterTestDemo();