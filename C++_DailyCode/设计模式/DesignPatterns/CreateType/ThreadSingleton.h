#pragma once
#include <iostream>
#include <mutex>
#include <thread>
using std::cout;
using std::endl;
using std::mutex;
using std::thread;

// 多线程单例模式
class ThreadSingleton
{
public:
	static ThreadSingleton* getInstance();

public:
	void setCount(int count) { m_count = count; }
	int getCount() { return m_count; }

private:
	ThreadSingleton() { m_count = 0; }
	~ThreadSingleton() { cout << "Instance Release Done." << endl; }

private:
	static ThreadSingleton* pInstance;
	static mutex InstanceLock;
	int m_count;

private:
	class ThreadSingletonRelease
	{
	public:
		~ThreadSingletonRelease();
	};
};

// 多线程单例模式测试函数
void ThreadSingletonTestDemo();
void ThreadSingletonTask();