#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
using namespace std;

/*二叉平衡树功能测试						**/
void funcCallBinaryBalanceTreeSearch();


/*二叉平衡树节点							**/
typedef struct DATA_TYPE_BINARY_BALANCE_NODE
{
	int										iVal;
	int										iIndex;
	int										iHeight;
	DATA_TYPE_BINARY_BALANCE_NODE*			pLeftChildNode;
	DATA_TYPE_BINARY_BALANCE_NODE*			pRightChildNode;

	DATA_TYPE_BINARY_BALANCE_NODE()
	{
		iVal								= 0;
		iIndex								= 0;
		iHeight								= 0;
		pLeftChildNode						= nullptr;
		pRightChildNode						= nullptr;
	}

	DATA_TYPE_BINARY_BALANCE_NODE(int val, int idx, int height, DATA_TYPE_BINARY_BALANCE_NODE* pLeft, DATA_TYPE_BINARY_BALANCE_NODE* pRight)
	{
		iVal								= val;
		iIndex								= idx;
		iHeight								= height;
		pLeftChildNode						= pLeft;
		pRightChildNode						= pRight;
	}

}BinBalanceNode;

/*二叉平衡树							**/
class BinaryBalanceTree
{
public:
	BinaryBalanceTree();
	~BinaryBalanceTree();

public:
	void	createTree(const vector<int>& vec);
	int		getIndex(int val);

private:
	bool	insertNode(BinBalanceNode*& pNode, int val, int idx);
	void	updateHeight(BinBalanceNode* pNode);
	int		getHeight(BinBalanceNode* pNode);
	void	rollTreeByLL(BinBalanceNode*& pNode);
	void	rollTreeByRR(BinBalanceNode*& pNode);
	void	rollTreeByLR(BinBalanceNode*& pNode);
	void	rollTreeByRL(BinBalanceNode*& pNode);
	void	destoryTree(BinBalanceNode* pNode);

private:
	BinBalanceNode*	 m_pRootNode;
};