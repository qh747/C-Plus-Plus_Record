#pragma once
#include <iostream>
#include <vector>
using namespace std;

/*二叉树遍历类型															**/
typedef enum TYPE_BTREE_FOREACH
{
	FIRST_SEQ_FOREACH				= 0,									// 先序遍历
	MIDDLE_SEQ_FOREACH				= 1,									// 中序遍历
	LAST_SEQ_FOREACH				= 2,									// 后序遍历

}BtreeForach_t;

/*二叉树节点类型															**/
typedef struct DATA_TYPE_BINARY_TREE_NODE
{
	int								iData;
	DATA_TYPE_BINARY_TREE_NODE*		pLeftNode;
	DATA_TYPE_BINARY_TREE_NODE*		pRightNode;

	DATA_TYPE_BINARY_TREE_NODE()
	{
		memset(this, 0, sizeof(DATA_TYPE_BINARY_TREE_NODE));
	}

	DATA_TYPE_BINARY_TREE_NODE(int data)
	{
		this->iData					= data;
		this->pLeftNode				= NULL;
		this->pRightNode			= NULL;
	}

}BTreeNode_dt;

/*二叉树																	**/
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

public:
	bool						addNewNode(int val);															// 添加新节点
	int							getLeafNodeCount();																// 获取叶子节点个数
	int							getTreeDepth();																	// 获取二叉树深度
	void						foreachTree(BtreeForach_t type);												// 遍历二叉树
	BinaryTree*					copyBinaryTree();																// 拷贝二叉树

private:
	void						freeTree(BTreeNode_dt** pRootNodeAddr);											// 释放二叉树
	int							countLeafNode(BTreeNode_dt* pRootNode);											// 统计叶子节点(类内部使用)
	int							countTreeDepth(BTreeNode_dt* pRootNode);										// 获取二叉树的深度(类内部使用)
	void						foreachTree(BTreeNode_dt* pRootNode, BtreeForach_t type);						// 二叉树遍历(类内部使用)
	BTreeNode_dt*				copyBinaryTree(BTreeNode_dt* pRootNode, vector<BTreeNode_dt*>& nodeMgmtVec);	// 拷贝二叉树

private:
	BTreeNode_dt*				m_pRootNode;																	// 二叉树根节点
	vector<BTreeNode_dt*>		m_nodeMgmtVec;																	// 二叉树管理数组
	int							m_leafNodeCount;																// 二叉树叶子节点个数
};