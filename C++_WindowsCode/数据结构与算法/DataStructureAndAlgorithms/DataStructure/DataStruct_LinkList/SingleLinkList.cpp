#include "SingleLinkList.h"

SingleLinkList::SingleLinkList() : m_pHeadNode(NULL)
{
	this->initLinkList();
}

SingleLinkList::~SingleLinkList()
{
	this->destoryLinkList();
}

void SingleLinkList::pushFront(int data)
{
	if (NULL == m_pHeadNode)
		return;

	LinkNode_dt* pNewNode = this->creatNode(data);

	pNewNode->pNext = m_pHeadNode->pNext;
	m_pHeadNode->pNext = pNewNode;
	m_pHeadNode->iData += 1;
}

void SingleLinkList::pushBack(int data)
{
	if (NULL == m_pHeadNode)
		return;

	LinkNode_dt* pPreviousNode = m_pHeadNode;
	for (int i = 0; i < m_pHeadNode->iData; ++i)
	{
		pPreviousNode = pPreviousNode->pNext;
	}
	
	if (NULL != pPreviousNode)
	{
		LinkNode_dt* pNewNode = this->creatNode(data);
		pPreviousNode->pNext = pNewNode;
		m_pHeadNode->iData += 1;
	}
}

void SingleLinkList::insert(size_t index, int data)
{
	if (index > m_pHeadNode->iData)
		return;

	LinkNode_dt* pPreviousNode = m_pHeadNode;
	LinkNode_dt* pNextNode = m_pHeadNode->pNext;
	for (int i = 0; i < index; ++i)
	{
		pPreviousNode = pNextNode;
		pNextNode = pNextNode->pNext;
	}

	if (NULL != pPreviousNode)
	{
		LinkNode_dt* pNewNode = this->creatNode(data);
		pPreviousNode->pNext = pNewNode;
		pNewNode->pNext = pNextNode;
		m_pHeadNode->iData += 1;
	}
}

void SingleLinkList::erase(size_t index)
{
	if (index >= m_pHeadNode->iData)
		return;

	LinkNode_dt* pPreviousNode = m_pHeadNode;
	LinkNode_dt* pNextNode = m_pHeadNode->pNext;
	for (int i = 0; i < index; ++i)
	{
		pPreviousNode = pNextNode;
		pNextNode = pNextNode->pNext;
	}

	if (NULL != pNextNode)
	{
		pPreviousNode->pNext = pNextNode->pNext;
		delete pNextNode;
		m_pHeadNode->iData -= 1;
	}
}

int& SingleLinkList::at(size_t index)
{
	if (index >= m_pHeadNode->iData)
		throw "INDEX INVALID";

	LinkNode_dt* pNode = m_pHeadNode->pNext;
	for (int i = 0; i < index; ++i)
	{
		pNode = pNode->pNext;
	}

	if(NULL == pNode)
		throw "LINK LIST ERROR";
	else
		return pNode->iData;
}

const int& SingleLinkList::at(size_t index) const
{
	return this->at(index);
}

size_t SingleLinkList::size()
{
	if (NULL == m_pHeadNode)
		return 0;
	else
		return m_pHeadNode->iData;
}

void SingleLinkList::clear()
{
	this->releaseLinkList();
}

SingleLinkList::LinkNode_dt* SingleLinkList::creatNode(int data)
{
	LinkNode_dt* pNewNode = new LinkNode_dt();
	pNewNode->iData = data;
	pNewNode->pNext = NULL;

	return pNewNode;
}

void SingleLinkList::initLinkList()
{
	if (NULL != m_pHeadNode)
		return;
	else
	{
		m_pHeadNode = new LinkNode_dt();
		m_pHeadNode->iData = 0;																// 首部节点的数据域存储节点个数
		m_pHeadNode->pNext = NULL;
	}
}

void SingleLinkList::releaseLinkList()
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

void SingleLinkList::destoryLinkList()
{
	this->releaseLinkList();

	if (NULL != m_pHeadNode)
		delete m_pHeadNode;
}