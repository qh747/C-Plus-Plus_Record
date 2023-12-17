#pragma once
#include <iostream>
#include <cstdlib>
#include <stack>
using namespace std;

/*二叉树节点类型										**/
typedef struct DATA_TYPE_BINARY_TREE_NODE
{
	char							cData;
	DATA_TYPE_BINARY_TREE_NODE*		pLeftNode;
	DATA_TYPE_BINARY_TREE_NODE*		pRightNode;

	DATA_TYPE_BINARY_TREE_NODE()
	{
		memset(this, 0, sizeof(DATA_TYPE_BINARY_TREE_NODE));
	}

	DATA_TYPE_BINARY_TREE_NODE(char data)
	{
		this->cData = data;
		this->pLeftNode = NULL;
		this->pRightNode = NULL;
	}
}BTreeNode_dt;