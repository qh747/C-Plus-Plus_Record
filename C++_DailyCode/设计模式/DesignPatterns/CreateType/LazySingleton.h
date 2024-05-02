#pragma once
#include <iostream>
using std::cout;
using std::endl;

// 饿汉式单例模式
class LazySingleton
{
public:
	static LazySingleton* getInstance();

public:
	void setCount(int count) { m_count = count; }
	int getCount() { return m_count; }

private:
	LazySingleton() { m_count = 0; }
	~LazySingleton() { cout << "Instance Release Done." << endl; }

private:
	static LazySingleton* pInstance;
	int m_count;

private:
	class LazySingletonRelease
	{
	public:
		~LazySingletonRelease();
	};
};

// 饿汉式单例模式测试函数
void LazySingletonTestDemo();