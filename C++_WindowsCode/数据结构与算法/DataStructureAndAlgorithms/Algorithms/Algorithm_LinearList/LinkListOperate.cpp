#include "LinkListOperate.h"

/*链表反转													**/
void funcLinkListReverse()
{
	/*创建链表												**/
	LinkListNode_dt headerNode(0, NULL);
	LinkListNode_dt* pHeader = &headerNode;
	for (int i = 1; i <= 10; ++i)
	{
		LinkListNode_dt* pCur = new LinkListNode_dt(i, NULL);
		pHeader->pNext = pCur;
		pHeader = pHeader->pNext;

		++headerNode.iVal;
	}

	/*打印链表												**/
	cout << "Before Reverse. Link List: ";
	LinkListNode_dt* pPrintBefore = headerNode.pNext;
	for (int i = 0; i < headerNode.iVal; ++i)
	{
		cout << pPrintBefore->iVal << " ";
		pPrintBefore = pPrintBefore->pNext;
	}
	cout << endl;

	/*链表反转												**/
	LinkListNode_dt* pPrevious = headerNode.pNext;
	LinkListNode_dt* pCurrent = pPrevious->pNext;
	LinkListNode_dt* pTemp = NULL;
	while (NULL != pCurrent)
	{
		pTemp = pCurrent->pNext;							// 暂存当前节点的下一个节点地址

		pCurrent->pNext = pPrevious;						// 反转当前节点指向
		pPrevious = pCurrent;								// 前一个节点前进到当前节点
		pCurrent = pTemp;									// 当前节点指前进到下一个节点
	}
	headerNode.pNext = pPrevious;							// 当前节点已经指向最后一个节点的下一个位置, 为空, 因此头节点的指针域指向前一个节点

	/*打印链表												**/
	cout << "After Reverse. Link List: ";
	LinkListNode_dt* pPrintAfter = headerNode.pNext;
	for (int i = 0; i < headerNode.iVal; ++i)
	{
		cout << pPrintAfter->iVal << " ";
		pPrintAfter = pPrintAfter->pNext;
	}
	cout << endl;

	/*销毁链表												**/
	LinkListNode_dt* pDestory = headerNode.pNext;
	LinkListNode_dt* pTempSave = NULL;
	for (int i = 0; i < headerNode.iVal; ++i)
	{
		pTempSave = pDestory->pNext;
		delete pDestory;
		
		pDestory = pTempSave;
	}
}