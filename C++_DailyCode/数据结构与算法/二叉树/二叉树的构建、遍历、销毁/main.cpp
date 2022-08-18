#include <iostream>
#include <stack>
#include <cstdlib>
using namespace std;

/*二叉树节点结构    **/
struct BTreeNode
{
	char m_data;
	BTreeNode* m_leftChildPtr;
	BTreeNode* m_rightChildPtr;

	BTreeNode() 
	{
		memset(this, 0, sizeof(BTreeNode));
	}

	BTreeNode(char data, BTreeNode* leftPtr = NULL, BTreeNode* rightPtr = NULL) : m_data(data), m_leftChildPtr(leftPtr), m_rightChildPtr(rightPtr)
	{

	}

	~BTreeNode()
	{
		cout << "Destory Node: " << m_data << endl;
	}
};

/*二叉树遍历节点结构    **/
struct BTreeForeachNode
{
	BTreeNode* m_curNodePtr;
	bool m_flag;
};

/*二叉树非递归遍历    **/
void foreachBTree(BTreeNode* curRoot);

/*二叉树释放函数    **/
void freeBTree(BTreeNode* curRoot);

/*二叉树构建函数    **/
BTreeNode* buildBTree();

int main()
{
	BTreeNode* pBTree = buildBTree();
	if (NULL != pBTree)
	{
		foreachBTree(pBTree);

		cout << endl;

		freeBTree(pBTree);
	}

	system("pause");
	return 0;
}

/*二叉树非递归遍历    **/
void foreachBTree(BTreeNode* curRoot)
{
	BTreeForeachNode node;
	node.m_curNodePtr = curRoot;
	node.m_flag = false;

	stack<BTreeForeachNode> foreachStack;
	foreachStack.push(node);

	while (false == foreachStack.empty())
	{
		BTreeForeachNode popNode = foreachStack.top();
		foreachStack.pop();

		if (false == popNode.m_flag)
		{
			/*压入当前节点的右子树节点    **/
			if (NULL != popNode.m_curNodePtr->m_rightChildPtr)
			{
				BTreeForeachNode rightNode;
				rightNode.m_curNodePtr = popNode.m_curNodePtr->m_rightChildPtr;
				rightNode.m_flag = false;

				foreachStack.push(rightNode);
			}

			/*压入当前节点的左子树节点    **/
			if (NULL != popNode.m_curNodePtr->m_leftChildPtr)
			{
				BTreeForeachNode leftNode;
				leftNode.m_curNodePtr = popNode.m_curNodePtr->m_leftChildPtr;
				leftNode.m_flag = false;

				foreachStack.push(leftNode);
			}

			/*压入当前节点    **/
			popNode.m_flag = true;
			foreachStack.push(popNode);
		}
		else
		{
			cout << "Current Node: " << popNode.m_curNodePtr->m_data << endl;
		}
	}
}

/*二叉树释放函数    **/
void freeBTree(BTreeNode* curRoot)
{
	if (NULL == curRoot)
		return;
	else
	{
		freeBTree(curRoot->m_leftChildPtr);
		freeBTree(curRoot->m_rightChildPtr);

		delete curRoot;
		curRoot = NULL;
	}
}

/*二叉树构建函数    **/
BTreeNode* buildBTree()
{
	BTreeNode* pRootNode = new BTreeNode('a');
	BTreeNode* pFstNode = new BTreeNode('b');
	BTreeNode* pSecNode = new BTreeNode('c');
	BTreeNode* pThrNode = new BTreeNode('d');
	BTreeNode* pFourNode = new BTreeNode('e');
	BTreeNode* pFiveNode = new BTreeNode('f');
	BTreeNode* pSixNode = new BTreeNode('g');

	pRootNode->m_leftChildPtr = pFstNode;
	pRootNode->m_rightChildPtr = pSecNode;

	pFstNode->m_leftChildPtr = pThrNode;
	pFstNode->m_rightChildPtr = pFourNode;

	pSecNode->m_leftChildPtr = pFiveNode;
	pSecNode->m_rightChildPtr = pSixNode;

	return pRootNode;
}