#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

/*动态数组改进版 (类型: int)														**/
class DynamicArrayAdv
{
public:
	typedef enum TYPE_ARRAY_SIZE
	{
		DFT_ARRAY_SIZE				= 8,											// 默认型数组大小
		SIMPLE_ARRAY_SIZE			= 64,											// 标准型数组大小
		EXTEND_ARRAY_SIZE			= 512,											// 拓展型数组大小
	}ArraySize_t;

public:
	DynamicArrayAdv();
	~DynamicArrayAdv();

public:
	void							pushBack(int val);								// 添加数据元素
	void							insert(size_t pos, int val);					// 插入数据元素
	void							erase(size_t pos);								// 移除数据元素
	void							clear();										// 清空数组

public:
	int&							operator[](size_t pos);							// 获取数组元素
	const int&						operator[](size_t pos) const;					// 获取数组元素

	int&							at(size_t pos);									// 获取数组元素
	const int&						at(size_t pos) const;							// 获取数组元素

public:
	size_t							size() { return m_arraySize; }					// 获取数组元素个数
	size_t							capacity() { return m_arrayCapacity; }			// 获取数组容量

private:
	void							initArray();									// 初始化数组
	void							extendArray(size_t size);						// 扩充数组
	void							moveBack(size_t pos);							// 数组元素向后移动
	void							moveForward(size_t pos);						// 数组元素向前移动

private:
	size_t							m_arraySize;									// 数组元素个数
	size_t							m_arrayCapacity;								// 数组容量
	int*							m_pArray;										// 数组指针
	int								m_arrayBuffer[DFT_ARRAY_SIZE];					// 数组缓冲区
};