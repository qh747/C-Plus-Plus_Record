#pragma once
#include <iostream>
using namespace std;

/*链表节点结构												**/
typedef struct DATA_TYPE_LINK_LIST_NODE
{
	int								iVal;					// 数据域
	DATA_TYPE_LINK_LIST_NODE*		pNext;					// 指针域

	DATA_TYPE_LINK_LIST_NODE()
	{
		iVal = -1;
		pNext = NULL;
	}
	DATA_TYPE_LINK_LIST_NODE(int val, DATA_TYPE_LINK_LIST_NODE* pNode)
	{
		iVal = val;
		pNext = pNode;
	}
}LinkListNode_dt;


/*链表反转													**/
void	funcLinkListReverse();