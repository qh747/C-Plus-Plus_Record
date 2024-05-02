#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// 子系统类
class FileSystem
{
public:
	void startFileSystem() { cout << "File System Start." << endl; }
	void closeFileSystem() { cout << "File System Close." << endl; }
};

class IOSystem
{
public:
	void startIOSystem() { cout << "IO System Start." << endl; }
	void closeIOSystem()  { cout << "IO System Close." << endl; }
};

class GraphWindowSystem
{
public:
	void startGraphWindowSystem() { cout << "GraphWindow System Start." << endl; }
	void closeGraphWindowSystem() { cout << "GraphWindow System Close." << endl; }
};

// 外观类
class Facade
{
public:
	Facade(FileSystem* pF, IOSystem* pIO, GraphWindowSystem* pG) : m_pFileSys(pF), m_pIOSys(pIO), m_pGraphWinSys(pG) {}
	virtual ~Facade() {}

public:
	virtual void start();
	virtual void close();

private:
	FileSystem* m_pFileSys;
	IOSystem*	m_pIOSys;
	GraphWindowSystem* m_pGraphWinSys;
};

// 外观模式测试函数
void FacadeTestDemo();