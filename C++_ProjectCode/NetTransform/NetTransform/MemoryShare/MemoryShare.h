#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <atomic>
#include <Windows.h>
using namespace std;

/*共享内存数据结构																											**/
typedef struct DATA_TYPE_MEMORY_SHARE_STRUCTURE
{
	int						iMemId;																							// 共享内存标识ID
	string					sMemName;																						// 共享内存名称
	HANDLE					pMemHandle;																						// 共享内存句柄
	LPVOID					pMemory;																						// 共享内存操作指针
	DWORD					ulMemSize;																						// 共享内存大小

	DATA_TYPE_MEMORY_SHARE_STRUCTURE()
	{
		iMemId				= -1;
		sMemName			= "";
		pMemHandle			= NULL;
		pMemory				= NULL;
		ulMemSize			= 0;
	}
}MemShareStruct_dt;

/*共享内存类																												**/
class MemoryShare
{
public:
	MemoryShare();																											// 构造函数
	virtual ~MemoryShare();																									// 析构函数

public:
	bool									allocateMemory(int id, const char* name, DWORD size, double sec);				// 申请内存
	bool									releaseMemory(int id, double sec);												// 释放内存
	bool									clearMemory(int id, DWORD pos, DWORD clearSize, double sec);					// 清空指定大小的内存空间

	DWORD									getMemorySize(int id, double sec);												// 获取共享内存大小
	DWORD									writeData(int id, void* pData, DWORD dataSize, DWORD pos, double sec);			// 写数据
	DWORD									readData(int id, void* pData, DWORD dataSize, DWORD pos, double sec);			// 读数据

private:																													// 禁止拷贝
	MemoryShare(const MemoryShare& other) {}
	void operator=(const MemoryShare& other) {}

private:
	void									setMemoryShareState(bool state);												// 设置MemoryShare类状态
	bool									getMemoryShareState();															// 获取MemoryShare类状态

private:
	bool									m_memoryShareState;																// 判断当前MemoryShare类是否可用

private:
	static DWORD							GETMemorySize(int id, double sec);												// 获取共享内存空间大小
	static DWORD							WRITEMemory(int id, void* pData, DWORD dataSize, DWORD pos, double sec);		// 共享内存写入数据
	static DWORD							READMemory(int id, void* pData, DWORD dataSize, DWORD pos, double sec);			// 共享内存读取数据
	static bool								CLEARMemory(int id, DWORD pos, DWORD clearSize, double sec);					// 共享内存清除数据
	static void								CLEARMemManageMap();															// 清空共享内存管理map
	static bool								ALLOCATEMemory(int id, const char* name, DWORD size, double sec);				// 申请共享内存空间
	static bool								RELEASEMemory(int id, double sec);												// 移除memory数据

	static bool								CREATEMemManageMapMutex();														// 共享内存管理map互斥量创建
	static bool								RELEASEMemManageMapMutex();														// 共享内存管理map互斥量销毁
	static bool								LOCKMemManageMapMutex(double sec);												// 共享内存管理map互斥量加锁
	static bool								UNLOCKMemManageMapMutex();														// 共享内存管理map互斥量解锁

	static void								ADDMemoryShareObject();															// 增加共享内存类对象
	static void								REDUCEMemoryShareObject();														// 减少共享内存类对象

private:
	static map<int, MemShareStruct_dt>		GBLMemManageMap;																// 共享内存管理map
	static HANDLE							GBLMemManageMapMutex;															// 共享内存管理map互斥量
	static atomic<unsigned long>			GBLMemoryShareObjects;															// 共享内存类对象记录
};