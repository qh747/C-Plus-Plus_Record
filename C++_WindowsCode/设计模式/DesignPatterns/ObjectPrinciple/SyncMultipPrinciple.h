#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// 车类
class AbstractCar
{
public:
	AbstractCar(const string& name) : m_carName(name) {}
	virtual ~AbstractCar() {}
	virtual string getCarName() { return m_carName; }

protected:
	string m_carName;
};

class SmallCar : public AbstractCar
{
public:
	SmallCar(const string& name) : AbstractCar(name) {}
	virtual ~SmallCar() {}
	virtual string getCarName() { return "Small Car: " + m_carName; }
};

class BigCar : public AbstractCar
{
public:
	BigCar(const string& name) : AbstractCar(name) {}
	virtual ~BigCar() {}
	virtual string getCarName() { return "Big Car: " + m_carName; }
};

// 人类
class Person
{
public:
	Person() : m_pCar(nullptr) {}
	~Person()
	{
		if (nullptr != nullptr)
			delete m_pCar;
	}

public:
	void buyCar(const string& carName, int size);
	void useCar();

private:
	// 车类与人类满足组合关系
	AbstractCar* m_pCar;	
};

// 合成复用测试函数
void SyncMultipPrincipleTestDemo();