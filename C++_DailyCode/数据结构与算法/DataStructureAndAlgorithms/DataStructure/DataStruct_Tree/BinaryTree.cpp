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
	else
	{
		/*后序遍历: 左右根											**/
		this->foreachTree(pRootNode->pLeftNode, type);
		this->foreachTree(pRootNode->pRightNode, type);
		cout << pRootNode->iData << " ";
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