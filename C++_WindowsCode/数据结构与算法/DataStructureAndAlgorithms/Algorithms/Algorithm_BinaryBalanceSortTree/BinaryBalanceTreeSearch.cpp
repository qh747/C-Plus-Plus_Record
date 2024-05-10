#include "BinaryBalanceTreeSearch.h"

/*二叉平衡排序树功能测试					**/
void funcCallBinaryBalanceTreeSearch()
{
	vector<int> intVec = initializer_list<int>{ 0, 33, 21, 51, 98, 65, 71 ,18, 45, 100, 32, 27, 78, 91, 73, 999 };
	BinaryBalanceTree binBanlanceTree;
	binBanlanceTree.createTree(intVec);

	cout << "Test Vec: ";
	for_each(intVec.begin(), intVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	/*第一组数据测试												**/
	cout << "Val " << 33 << " In ";
	int fstValIndex = binBanlanceTree.getIndex(33);
	cout << fstValIndex << endl;

	/*第二组数据测试												**/
	cout << "Val " << 71 << " In ";
	int secValIndex = binBanlanceTree.getIndex(71);
	cout << secValIndex << endl;

	/*第三组数据测试												**/
	cout << "Val " << 100 << " In ";
	int trdValIndex = binBanlanceTree.getIndex(100);
	cout << trdValIndex << endl;

	/*第四组数据测试												**/
	cout << "Val " << 77 << " In ";
	int forthValIndex = binBanlanceTree.getIndex(77);
	cout << forthValIndex << endl;
}


/*二叉平衡排序树							**/
BinaryBalanceTree::BinaryBalanceTree()
{
	m_pRootNode = nullptr;
}

BinaryBalanceTree::~BinaryBalanceTree()
{
	if (nullptr != m_pRootNode)
		this->destoryTree(m_pRootNode);
}

void BinaryBalanceTree::createTree(const vector<int>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		this->insertNode(m_pRootNode, vec[i], i);
	}
}

bool BinaryBalanceTree::insertNode(BinBalanceNode*& pNode, int val, int idx)
{
	if (nullptr == pNode)
	{
		/*创建新节点, 存储数据元素										**/
		pNode = new BinBalanceNode(val, idx, 0, nullptr, nullptr);
		return true;
	}
	
	if (pNode->iVal == val)
	{
		/*节点已存在, 创建失败											**/
		return false;
	}
	else if (val < pNode->iVal)
	{
		/*插入新节点													**/
		bool res = this->insertNode(pNode->pLeftChildNode, val, idx);
		if (!res)
			return false;

		/*新节点插入成功, 更新位置信息									**/
		this->updateHeight(pNode);

		/*判断当前节点的左子树和右子树高度								**/
		int leftHeight = (nullptr != pNode->pLeftChildNode) ? pNode->pLeftChildNode->iHeight : 0;
		int rightHeight = (nullptr != pNode->pRightChildNode) ? pNode->pRightChildNode->iHeight : 0;
		int heightDiff = leftHeight - rightHeight;
		if (heightDiff > 1)
		{
			/*左子树高度超过右子树高度, 进行右旋调整					**/
			this->rollTreeByRR(pNode);
		}
		else if (heightDiff < -1)
		{
			/*左子树高度低于右子树高度, 先进行左旋调整, 再进行右旋调整	**/
			this->rollTreeByLR(pNode);
		}

		return true;
	}
	else if (val > pNode->iVal)
	{
		/*插入新节点													**/
		bool res = this->insertNode(pNode->pRightChildNode, val, idx);
		if (!res)
			return false;

		/*新节点插入成功, 更新位置信息									**/
		this->updateHeight(pNode);

		/*判断当前节点的左子树和右子树高度								**/
		int leftHeight = (nullptr != pNode->pLeftChildNode) ? pNode->pLeftChildNode->iHeight : 0;
		int rightHeight = (nullptr != pNode->pRightChildNode) ? pNode->pRightChildNode->iHeight : 0;
		int heightDiff = leftHeight - rightHeight;
		if (heightDiff > 1)
		{
			/*左子树高度超过右子树高度, 先进行右旋调整, 再进行左旋调整	**/
			this->rollTreeByRL(pNode);
		}
		else if (heightDiff < -1)
		{
			/*左子树高度低于右子树高度, 进行左旋调整					**/
			this->rollTreeByLL(pNode);
		}

		return true;
	}
	else
		return false;
}

int BinaryBalanceTree::getIndex(int val)
{
	BinBalanceNode* pNode = m_pRootNode;
	while (nullptr != pNode)
	{
		if (pNode->iVal == val)
			return pNode->iIndex;
		else if (val < pNode->iVal)
			pNode = pNode->pLeftChildNode;
		else
			pNode = pNode->pRightChildNode;
	}

	return -1;
}

void BinaryBalanceTree::updateHeight(BinBalanceNode* pNode)
{
	if (nullptr == pNode)
		return;
	else
	{
		/*获取当前节点的左孩子节点高度					**/
		int leftHeight = (nullptr != pNode->pLeftChildNode) ? pNode->pLeftChildNode->iHeight : 0;

		/*获取当前节点的右孩子节点高度					**/
		int rightHeight = (nullptr != pNode->pRightChildNode) ? pNode->pRightChildNode->iHeight : 0;

		/*当前节点的高度为左、右孩子节点高度最大值 + 1	**/
		pNode->iHeight = max(leftHeight, rightHeight) + 1;
	}
}

int	BinaryBalanceTree::getHeight(BinBalanceNode* pNode)
{
	if (nullptr == pNode)
		return 0;
	else
		return pNode->iHeight;
}

void BinaryBalanceTree::rollTreeByLL(BinBalanceNode*& pNode)
{
	BinBalanceNode* pRootNode = pNode;

	/*晋升当前节点的右孩子节点							**/
	BinBalanceNode* pUpNode = pNode->pRightChildNode;

	/*当前节点的右孩子节点指向晋升节点的左孩子节点		**/
	pRootNode->pRightChildNode = pUpNode->pLeftChildNode;

	/*晋升节点的左孩子节点指向当前节点					**/
	pUpNode->pLeftChildNode = pRootNode;

	/*当前节点修改指向为晋升节点						**/
	pNode = pUpNode;

	/*更新节点高度										**/
	this->updateHeight(pUpNode->pLeftChildNode);
	this->updateHeight(pUpNode->pRightChildNode);
	this->updateHeight(pUpNode);
}

void BinaryBalanceTree::rollTreeByRR(BinBalanceNode*& pNode)
{
	BinBalanceNode* pRootNode = pNode;

	/*晋升当前节点的左孩子节点							**/
	BinBalanceNode* pUpNode = pNode->pLeftChildNode;

	/*当前节点的左孩子节点指向晋升节点的右孩子节点		**/
	pNode->pLeftChildNode = pUpNode->pRightChildNode;

	/*晋升节点的右孩子节点指向当前节点					**/
	pUpNode->pRightChildNode = pNode;

	/*当前节点修改指向为晋升节点						**/
	pNode = pUpNode;

	/*更新节点高度										**/
	this->updateHeight(pUpNode->pLeftChildNode);
	this->updateHeight(pUpNode->pRightChildNode);
	this->updateHeight(pUpNode);
}

void BinaryBalanceTree::rollTreeByLR(BinBalanceNode*& pNode)
{
	/*先将当前节点的左孩子节点作为根节点进行左旋调整	**/
	this->rollTreeByLL(pNode->pLeftChildNode);

	this->updateHeight(pNode->pLeftChildNode);
	this->updateHeight(pNode->pRightChildNode);
	this->updateHeight(pNode);

	/*再将当前节点作为根节点进行右旋调整				**/
	this->rollTreeByRR(pNode);

	this->updateHeight(pNode->pLeftChildNode);
	this->updateHeight(pNode->pRightChildNode);
	this->updateHeight(pNode);
}

void BinaryBalanceTree::rollTreeByRL(BinBalanceNode*& pNode)
{
	/*先将当前节点的右孩子节点作为根节点进行右旋调整	**/
	this->rollTreeByRR(pNode->pRightChildNode);

	this->updateHeight(pNode->pLeftChildNode);
	this->updateHeight(pNode->pRightChildNode);
	this->updateHeight(pNode);

	/*再将当前节点作为根节点进行左旋调整				**/
	this->rollTreeByLL(pNode);

	this->updateHeight(pNode->pLeftChildNode);
	this->updateHeight(pNode->pRightChildNode);
	this->updateHeight(pNode);
}

void BinaryBalanceTree::destoryTree(BinBalanceNode* pNode)
{
	if (nullptr == pNode)
		return;

	this->destoryTree(pNode->pLeftChildNode);
	this->destoryTree(pNode->pRightChildNode);

	delete pNode;
}