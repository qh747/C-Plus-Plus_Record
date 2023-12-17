#include "DoubleLinkList.h"

DoubleLinkList::DoubleLinkList() : m_pHeadNode(NULL)
{
	this->initLinkList();
}

DoubleLinkList::~DoubleLinkList()
{
	this->destoryLinkList();
}

void DoubleLinkList::pushFront(int data)
{
	if (NULL == m_pHeadNode)
		return;

	LinkNode_dt* pNewNode = this->creatNode(data);

	LinkNode_dt* pOldNextNode = m_pHeadNode->pNext;
	m_pHeadNode->pNext = pNewNode;

	pNewNode->pPrevious = m_pHeadNode;
	pNewNode->pNext = pOldNextNode;

	pOldNextNode->pPrevious = pNewNode;

	m_pHeadNode->iData += 1;
}

void DoubleLinkList::pushBack(int data)
{
	if (NULL == m_pHeadNode)
		return;

	LinkNode_dt* pOldBackNode = m_pHeadNode;
	for (int i = 0; i < m_pHeadNode->iData; ++i)
	{
		pOldBackNode = pOldBackNode->pNext;
	}

	if (NULL != pOldBackNode)
	{
		LinkNode_dt* pNewBackNode = this->creatNode(data);
		
		pNewBackNode->pPrevious = pOldBackNode;
		pOldBackNode->pNext = pNewBackNode;

		m_pHeadNode->iData += 1;
	}
}

void DoubleLinkList::insert(size_t index, int data)
{
	if (index > m_pHeadNode->iData)
		return;

	LinkNode_dt* pPreviousNode = m_pHeadNode;
	for (int i = 0; i < index; ++i)
	{
		pPreviousNode = pPreviousNode->pNext;
	}

	if (NULL != pPreviousNode)
	{
		LinkNode_dt* pOldNextNode = pPreviousNode->pNext;

		LinkNode_dt* pNewNode = this->creatNode(data);
		pNewNode->pNext = pOldNextNode;
		pNewNode->pPrevious = pPreviousNode;

		pPreviousNode->pNext = pNewNode;

		if (NULL != pOldNextNode)
			pOldNextNode->pPrevious = pNewNode;
		
		m_pHeadNode->iData += 1;
	}
}

void DoubleLinkList::erase(size_t index)
{
	if (index >= m_pHeadNode->iData)
		return;

	LinkNode_dt* pPreviousNode = m_pHeadNode;
	for (int i = 0; i < index; ++i)
	{
		pPreviousNode = pPreviousNode->pNext;
	}

	if (NULL != pPreviousNode)
	{
		LinkNode_dt* pEraseNode = pPreviousNode->pNext;
		LinkNode_dt* pEraseNextNode = pEraseNode->pNext;

		pPreviousNode->pNext = pEraseNextNode;
		if (NULL != pEraseNextNode)
			pEraseNextNode->pPrevious = pPreviousNode;

		delete pEraseNode;
		m_pHeadNode->iData -= 1;
	}
}

int& DoubleLinkList::at(size_t index) 
{
	if (index >= m_pHeadNode->iData)
		throw "INDEX INVALID";

	LinkNode_dt* pNode = m_pHeadNode->pNext;
	for (int i = 0; i < index; ++i)
	{
		pNode = pNode->pNext;
	}

	if (NULL == pNode)
		throw "LINK LIST ERROR";
	else
		return pNode->iData;
}

const int& DoubleLinkList::at(size_t index) const
{
	return this->at(index);
}

size_t DoubleLinkList::size()
{
	if (NULL == m_pHeadNode)
		return 0;
	else
		return m_pHeadNode->iData;
}

void DoubleLinkList::clear()
{
	this->releaseLinkList();
}

DoubleLinkList::LinkNode_dt* DoubleLinkList::creatNode(int data)
{
	LinkNode_dt* pNewNode = new LinkNode_dt();
	pNewNode->iData = data;
	pNewNode->pPrevious = NULL;
	pNewNode->pNext = NULL;

	return pNewNode;
}

void DoubleLinkList::initLinkList()
{
	if (NULL != m_pHeadNode)
		return;
	else
	{
		m_pHeadNode = new LinkNode_dt();
		m_pHeadNode->iData = 0;									// 首部节点的数据域存储节点个数
		m_pHeadNode->pPrevious = NULL;
		m_pHeadNode->pNext = NULL;
	}
}

void DoubleLinkList::releaseLinkList()
{
	if (NULL == m_pHeadNode)
		return;

	LinkNode_dt* pTemp = m_pHeadNode->pNext;
	while (NULL != pTemp)
	{
		LinkNode_dt* pNext = pTemp->pNext;
		if (NULL != pTemp)
			delete pTemp;

		pTemp = pNext;
	}

	m_pHeadNode->iData = 0;
	m_pHeadNode->pNext = NULL;
}

void DoubleLinkList::destoryLinkList()
{
	this->releaseLinkList();

	if (NULL != m_pHeadNode)
		delete m_pHeadNode;
}