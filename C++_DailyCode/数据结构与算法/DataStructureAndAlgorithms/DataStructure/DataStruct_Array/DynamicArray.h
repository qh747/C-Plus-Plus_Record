#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

/*动态数组 (类型: int)												**/
class DynamicArray
{
public:
	DynamicArray();													// 构造
	DynamicArray(unsigned int capacity);							// 构造
	~DynamicArray();												// 析构

public:
	void					addVal(int val);						// 添加元素
	void					insertVal(unsigned int pos, int val);	// 插入元素
	void					modifyVal(unsigned int pos, int val);	// 修改元素
	int						getVal(unsigned int pos);				// 获取元素
	void					delVal(unsigned int pos);				// 移除元素
	void					clear();								// 清空数组
	unsigned int			getSize();								// 获取数组元素个数
	unsigned int			getCapacity();							// 获取数组容量大小

private:
	void					initArray(unsigned int capacity = 4);	// 初始化数组
	bool					extendArray(unsigned int capacity);		// 拓展数组

private:
	unsigned int			m_capacity;								// 数组容量
	unsigned int			m_size;									// 数组元素个数
	int*					m_pArray;								// 数组指针
};


