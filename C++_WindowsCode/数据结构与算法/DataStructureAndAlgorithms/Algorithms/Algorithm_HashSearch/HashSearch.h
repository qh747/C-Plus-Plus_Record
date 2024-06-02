#pragma once
#include <iostream>
#include <vector>
#include <ctime>
using std::cout;
using std::endl;
using std::vector;
using std::initializer_list;

/* 哈希节点											**/
typedef struct DATA_TYPE_HASH_NODE
{
	int						iIndex;					// 元素索引
	int						iValue;					// 元素值
	DATA_TYPE_HASH_NODE*	pNext;					// 下个节点的地址

	DATA_TYPE_HASH_NODE(int idx, int val) {
		iIndex = idx;
		iValue = val;
		pNext = nullptr;
	}

}HashNode_dt;

/* 哈希表											**/
class HashTable
{
public:
	HashTable(int primeNum = 13, int rebuildDeepth = 5);
	~HashTable();

public:
	void insert(int val);							// 插入元素
	bool erase(int val);							// 移除元素
	void modify(int oldVal, int newVal);			// 修改元素	
	bool search(int val);							// 查找元素
	int size() { return m_size; }					// 获取元素个数

private:
	void destoryHashTable();						// 销毁哈希表
	void rebuildHashTable();						// 重建哈希表
	int  calcBiggerPrimeNum();						// 计算更大的质数
	bool isPrime(int num);							// 判断参数num是否为质数

private:
	vector<HashNode_dt*>	m_nodeVec;				// 哈希节点数组
	int						m_primeNum;				// 质数
	int						m_rebuildHashDeepth;	// 哈希表重建门限
	int						m_size;					// 节点个数
};

/*哈希查找											**/
void funcHashSearch();