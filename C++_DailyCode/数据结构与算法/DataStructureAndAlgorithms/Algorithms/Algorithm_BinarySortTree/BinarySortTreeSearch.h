#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

/*¶þ²æÅÅÐòÊ÷¹¦ÄÜ²âÊÔ				**/
void funcCallBinarySortTreeSearch();

/*¶þ²æÅÅÐòÊ÷½ÚµãÀàÐÍ				**/
typedef struct DATA_TYPE_BINARY_SORT_NODE
{
	int								iVal;
	int								iIndex;
	DATA_TYPE_BINARY_SORT_NODE*		pLeftChildNode;
	DATA_TYPE_BINARY_SORT_NODE*		pRightChildNode;

	DATA_TYPE_BINARY_SORT_NODE()
	{
		memset(this, 0, sizeof(DATA_TYPE_BINARY_SORT_NODE));
	}

	DATA_TYPE_BINARY_SORT_NODE(int val, int idx, DATA_TYPE_BINARY_SORT_NODE* pLeft, DATA_TYPE_BINARY_SORT_NODE* pRight)
	{
		iVal						= val;
		iIndex						= idx;
		pLeftChildNode				= pLeft;
		pRightChildNode				= pRight;
	}

}BinSortNode_dt;

/*¶þ²æÅÅÐòÊ÷						**/
class BinarySortTree
{
public:
	BinarySortTree()	{ m_pRootNode = nullptr; }
	~BinarySortTree()	{ this->destroyTree(m_pRootNode); }

public:
	void				createTree(const vector<int>& vec);
	int					getIndex(int val);

private:
	void				insertNode(BinSortNode_dt** pCurNodeAddr, int val, int idx);
	void				destroyTree(BinSortNode_dt* pRootNode);

private:
	BinSortNode_dt*		m_pRootNode;
};