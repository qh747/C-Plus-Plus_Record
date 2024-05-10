#include "BinarySortTreeSearch.h"

/*二叉排序树功能测试				**/
void funcCallBinarySortTreeSearch()
{
	vector<int> intVec = initializer_list<int>{ 0, 33, 21, 51, 98, 65, 71 ,18, 45, 100, 32, 27, 78, 91, 73, 999 };
	BinarySortTree binSortTree;
	binSortTree.createTree(intVec);

	cout << "Test Vec: ";
	for_each(intVec.begin(), intVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	/*第一组数据测试												**/
	cout << "Val " << 33 << " In ";
	int fstValIndex = binSortTree.getIndex(33);
	cout << fstValIndex << endl;

	/*第二组数据测试												**/
	cout << "Val " << 71 << " In ";
	int secValIndex = binSortTree.getIndex(71);
	cout << secValIndex << endl;

	/*第三组数据测试												**/
	cout << "Val " << 100 << " In ";
	int trdValIndex = binSortTree.getIndex(100);
	cout << trdValIndex << endl;

	/*第四组数据测试												**/
	cout << "Val " << 77 << " In ";
	int forthValIndex = binSortTree.getIndex(77);
	cout << forthValIndex << endl;
}

void BinarySortTree::createTree(const vector<int>& vec)
{
	if (vec.empty())
		return;

	for (int i = 0; i < vec.size(); ++i)
	{
		this->insertNode(&m_pRootNode, vec[i], i);
	}
}

int BinarySortTree::getIndex(int val)
{
	if (!m_pRootNode)
		return -1;
	else
	{
		BinSortNode_dt* pCurNode = m_pRootNode;
		while (pCurNode)
		{
			if (pCurNode->iVal == val)
				return pCurNode->iIndex;
			else if (pCurNode->iVal < val)
				pCurNode = pCurNode->pRightChildNode;
			else
				pCurNode = pCurNode->pLeftChildNode;
		}

		return -1;
	}
}

void BinarySortTree::insertNode(BinSortNode_dt** pCurNodeAddr, int val, int idx)
{
	if (!*pCurNodeAddr)
	{
		/*当前节点为空则新创建节点存储元素										**/
		(*pCurNodeAddr) = new BinSortNode_dt(val, idx, nullptr, nullptr);
	}
	else
	{
		if ((*pCurNodeAddr)->iVal > val)
		{
			/*当前节点比给定元素大则递归判断当前节点的左孩子节点				**/
			this->insertNode(&((*pCurNodeAddr)->pLeftChildNode), val, idx);
		}
		else
		{
			/*当前节点比给定元素小则递归判断当前节点的右孩子节点				**/
			this->insertNode(&((*pCurNodeAddr)->pRightChildNode), val, idx);
		}		
	}
}

void BinarySortTree::destroyTree(BinSortNode_dt* pRootNode)
{
	if (pRootNode)
	{
		this->destroyTree(pRootNode->pLeftChildNode);
		this->destroyTree(pRootNode->pRightChildNode);

		delete pRootNode;
	}
}