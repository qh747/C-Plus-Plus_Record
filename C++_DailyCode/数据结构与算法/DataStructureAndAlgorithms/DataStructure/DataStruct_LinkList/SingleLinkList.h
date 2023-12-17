#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

/*单向链表 (类型: int)														**/
class SingleLinkList
{
public:
	typedef struct DATA_TYPE_LINK_NODE
	{
		int								iData;								// 数据
		DATA_TYPE_LINK_NODE*			pNext;								// 下个节点的地址
	}LinkNode_dt;

public:
	SingleLinkList();														// 构造
	~SingleLinkList();														// 析构

public:
	void								pushFront(int data);				// 添加元素(首部)
	void								pushBack(int data);					// 添加元素(尾部)
	void								insert(size_t index, int data);		// 插入元素
	void								erase(size_t index);				// 移除元素
	int&								at(size_t index);					// 获取元素(可修改)
	const int&							at(size_t index) const;				// 获取元素(不可修改)
	size_t								size();								// 获取链表长度
	void								clear();							// 清空链表

private:
	LinkNode_dt*						creatNode(int data);				// 创建节点
	void								initLinkList();						// 初始化链表
	void								releaseLinkList();					// 释放链表
	void								destoryLinkList();					// 销毁链表

private:
	LinkNode_dt*						m_pHeadNode;						// 链表首节点 
};