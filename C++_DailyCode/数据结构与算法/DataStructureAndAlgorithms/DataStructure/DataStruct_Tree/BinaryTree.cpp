#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	m_leafNodeCount = 0;
	m_pRootNode = nullptr;
	m_nodeMgmtVec.clear();
}

BinaryTree::~BinaryTree()
{
	if (m_pRootNode)
	{
		this->freeTree(&m_pRootNode);
		m_pRootNode = nullptr;
	}
}

bool BinaryTree::addNewNode(int val)
{
	BTreeNode_dt* pNewNode = new BTreeNode_dt(val);
	if (m_nodeMgmtVec.empty())
	{
		/*节点管理数组为空, 则插入根节点							**/
		m_nodeMgmtVec.push_back(pNewNode);
		m_pRootNode = pNewNode;
		
		return true;
	}
	else
	{
		/*节点管理数组不为空, 查找可插入的节点						**/
		BTreeNode_dt* pParentNode = nullptr;
		for (int i = 0; i < m_nodeMgmtVec.size(); ++i)
		{
			BTreeNode_dt* pCurNode = m_nodeMgmtVec[i];

			/*满足可插入节点的要求是左孩子或右孩子节点为空			**/
			if (!pCurNode->pLeftNode || !pCurNode->pRightNode)
			{
				pParentNode = pCurNode;
				break;
			}
		}

		if (pParentNode)
		{
			/*找到可插入节点										**/
			if (!pParentNode->pLeftNode)
				pParentNode->pLeftNode = pNewNode;
			else
				pParentNode->pRightNode = pNewNode;

			/*节点管理												**/
			m_nodeMgmtVec.push_back(pNewNode);

			return true;
		}
		else
		{
			delete pNewNode;
			cerr << "Binary Tree Error. Can Not Find valid Node To Insert." << endl;

			return false;
		}
	}
}

int	BinaryTree::getNodeCount()
{
	int nodeCount = this->countNode(m_pRootNode);
	return nodeCount;
}

int	BinaryTree::getLeafNodeCount()
{
	/*清空之前统计的叶子节点个数的缓存								**/
	m_leafNodeCount = 0;

	/*传入二叉树根节点, 递归计算叶子节点个数						**/
	this->countLeafNode(m_pRootNode);

	/*叶子节点个数在递归计算中已经统计完成, 已被赋值, 可以直接返回	**/
	return m_leafNodeCount;
}

int BinaryTree::getTreeDepth()
{
	int treeDepth = this->countTreeDepth(m_pRootNode);
	return treeDepth;
}

void BinaryTree::foreachTree(BtreeForach_t type)
{
	cout << "Binary Tree Start Foreach: ";
	this->BinaryTree::foreachTree(m_pRootNode, type);
	cout << endl;
}

BinaryTree* BinaryTree::copyBinaryTree()
{
	BinaryTree* pNewTree = new BinaryTree();
	pNewTree->m_pRootNode = BinaryTree::copyBinaryTree(m_pRootNode, pNewTree->m_nodeMgmtVec);

	return pNewTree;
}

void BinaryTree::freeTree(BTreeNode_dt** pRootNodeAddr)
{
	if (!(*pRootNodeAddr))
		return;
	else if((*pRootNodeAddr)->pLeftNode || (*pRootNodeAddr)->pRightNode)
	{
		/*先释放当前节点的叶子节点									**/
		this->freeTree(&((*pRootNodeAddr)->pLeftNode));
		this->freeTree(&((*pRootNodeAddr)->pRightNode));
	}
	
	/*释放当前节点													**/
	delete* pRootNodeAddr;
	*pRootNodeAddr = nullptr;
}

int BinaryTree::countNode(BTreeNode_dt* pRootNode)
{
	if (!pRootNode)
		return 0;
	else
	{
		int leftTreeCount = this->countNode(pRootNode->pLeftNode);
		int rightTreeCount = this->countNode(pRootNode->pRightNode);
		return leftTreeCount + rightTreeCount + 1;
	}
}

int BinaryTree::countLeafNode(BTreeNode_dt* pRootNode)
{
	if (!pRootNode)
		return 0;
	else if (!pRootNode->pLeftNode && !pRootNode->pRightNode)
	{
		++m_leafNodeCount;
		return m_leafNodeCount;
	}
	else
	{
		countLeafNode(pRootNode->pLeftNode);
		countLeafNode(pRootNode->pRightNode);
		return m_leafNodeCount;
	}
}

int BinaryTree::countTreeDepth(BTreeNode_dt* pRootNode)
{
	if (!pRootNode)
		return 0;
	else if (!pRootNode->pLeftNode && !pRootNode->pRightNode)
		return 1;
	else
	{
		int leftDepth = this->countTreeDepth(pRootNode->pLeftNode);
		int rightDepth = this->countTreeDepth(pRootNode->pRightNode);

		int curDepth = (leftDepth >= rightDepth) ? ++leftDepth : ++rightDepth;
		return curDepth;
	}
}

void BinaryTree::foreachTree(BTreeNode_dt* pRootNode, BtreeForach_t type)
{
	if (!pRootNode)
		return;
	
	if (FIRST_SEQ_FOREACH == type)
	{
		/*先序遍历: 根左右											**/
		cout << pRootNode->iData << " ";
		this->foreachTree(pRootNode->pLeftNode, type);
		this->foreachTree(pRootNode->pRightNode, type);
	}
	else if (MIDDLE_SEQ_FOREACH == type)
	{
		/*中序遍历: 左根右											**/
		this->foreachTree(pRootNode->pLeftNode, type);
		cout << pRootNode->iData << " ";
		this->foreachTree(pRootNode->pRightNode, type);
	}
	else if(LAST_SEQ_FOREACH == type)
	{
		/*后序遍历: 左右根											**/
		this->foreachTree(pRootNode->pLeftNode, type);
		this->foreachTree(pRootNode->pRightNode, type);
		cout << pRootNode->iData << " ";
	}
	else if(NON_RECURSION_FOREACH == type)
	{
		/*非递归遍历, 遍历顺序为中序遍历									**/
		BTreeNode_dt* pCurNode = pRootNode;
		stack<BTreeNode_dt*> foreachStack;
		while (pCurNode || !foreachStack.empty())
		{
			if (pCurNode)
			{
				/*当前节点存入栈, 当前节点修改指向为左孩子节点				**/
				foreachStack.push(pCurNode);
				pCurNode = pCurNode->pLeftNode;
			}
			else
			{
				/*当遍历到叶子节点时进入此流程, 从栈中获取上一个叶子节点	**/
				pCurNode = foreachStack.top();

				/*打印值, 并弹出当前节点									**/
				cout << pCurNode->iData << " ";
				foreachStack.pop();

				/*当前节点指向右孩子节点, 开启下一轮入栈					**/
				pCurNode = pCurNode->pRightNode;
			}
		}
	}
	else
	{
		/*层次遍历															**/
		queue<BTreeNode_dt*> foreachQueue;
		foreachQueue.push(pRootNode);
		while (!foreachQueue.empty())
		{
			/*获取当前节点的信息											**/
			BTreeNode_dt* pCurNode = foreachQueue.front();
			cout << pCurNode->iData << " ";
			foreachQueue.pop();

			/*当前节点的左孩子节点入队										**/
			if(pCurNode->pLeftNode)
				foreachQueue.push(pCurNode->pLeftNode);

			/*当前节点右孩子节点入队										**/
			if(pCurNode->pRightNode)
				foreachQueue.push(pCurNode->pRightNode);
		}
	}
}

BTreeNode_dt* BinaryTree::copyBinaryTree(BTreeNode_dt* pRootNode, vector<BTreeNode_dt*>& nodeMgmtVec)
{
	if (!pRootNode)
		return nullptr;
	else
	{
		BTreeNode_dt* pRightNode = this->copyBinaryTree(pRootNode->pRightNode, nodeMgmtVec);
		BTreeNode_dt* pLeftNode = this->copyBinaryTree(pRootNode->pLeftNode, nodeMgmtVec);

		BTreeNode_dt* pNewNode = new BTreeNode_dt(pRootNode->iData);
		pNewNode->pLeftNode = pLeftNode;
		pNewNode->pRightNode = pRightNode;

		nodeMgmtVec.insert(nodeMgmtVec.begin(), 1, pNewNode);

		return pNewNode;
	}
}