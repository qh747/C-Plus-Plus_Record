#include "BinaryTree.h"

void preorder(TreeNode* root)
{
	if (nullptr == root)
		return;

	cout << root->val << " ";
	preorder(root->left);
	preorder(root->right);
}

void inorder(TreeNode* root)
{
	if (nullptr == root)
		return;

	preorder(root->left);
	cout << root->val << " ";
	preorder(root->right);
}

void postorder(TreeNode* root)
{
	if (nullptr == root)
		return;

	preorder(root->left);
	preorder(root->right);
	cout << root->val << " ";
}

void cycle(TreeNode* root)
{
	if (nullptr == root)
		return;

	cycle(root->left);
	cycle(root->right);
	delete root;
}

vector<int> preorderTraversal_Solution::preorderTraversal(TreeNode* root) 
{
	vector<int> countVec;
	this->preorder(root, countVec);

	return countVec;
}

void preorderTraversal_Solution::preorder(TreeNode* root, vector<int>& vec)
{
	if (nullptr == root)
		return;

	// 递归遍历，按照前序遍历(根左右)二叉树
	vec.push_back(root->val);
	preorder(root->left, vec);
	preorder(root->right, vec);
}

void preorderTraversal_Solution::preorderTraversalTest()
{
	TreeNode fst(1);
	TreeNode sec(2);
	TreeNode thr(3);

	fst.left = &sec;
	fst.right = &thr;

	vector<int> vec = this->preorderTraversal(&fst);
	for (int i = 0; i < vec.size(); ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

vector<int> inorderTraversal_Solution::inorderTraversal(TreeNode* root)
{
	vector<int> countVec;
	this->inorder(root, countVec);

	return countVec;
}

void inorderTraversal_Solution::inorder(TreeNode* root, vector<int>& vec)
{
	if (nullptr == root)
		return;

	// 递归遍历，按照中序遍历(左根右)二叉树
	inorder(root->left, vec);
	vec.push_back(root->val);
	inorder(root->right, vec);
}

void inorderTraversal_Solution::inorderTraversalTest()
{
	TreeNode fst(1);
	TreeNode sec(2);
	TreeNode thr(3);

	fst.left = &sec;
	fst.right = &thr;

	vector<int> vec = this->inorderTraversal(&fst);
	for (int i = 0; i < vec.size(); ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

vector<int> postorderTraversal_Solution::postorderTraversal(TreeNode* root)
{
	vector<int> countVec;
	this->postorder(root, countVec);

	return countVec;
}

void postorderTraversal_Solution::postorder(TreeNode* root, vector<int>& vec)
{
	if (nullptr == root)
		return;

	// 递归遍历，按照后序遍历(左右根)二叉树
	postorder(root->left, vec);
	postorder(root->right, vec);
	vec.push_back(root->val);
}

void postorderTraversal_Solution::postorderTraversalTest()
{
	TreeNode fst(1);
	TreeNode sec(2);
	TreeNode thr(3);

	fst.left = &sec;
	fst.right = &thr;

	vector<int> vec = this->postorderTraversal(&fst);
	for (int i = 0; i < vec.size(); ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

int maxDepth_Solution::maxDepth(TreeNode* root)
{
	if (nullptr == root)
		return 0;

	// 递归获取左子树和右子树大小，并返回较大子树的深度
	int leftLength = this->maxDepth(root->left);
	int rightLength = this->maxDepth(root->right);
	return (leftLength > rightLength) ? ++leftLength : ++rightLength;
}

void maxDepth_Solution::maxDepthTest()
{
	TreeNode fst(1);
	TreeNode sec(2);
	TreeNode thr(3);

	fst.left = &sec;
	fst.right = &thr;

	int depth = this->maxDepth(&fst);
	cout << depth << endl;
}

TreeNode* Convert_Solution::Convert(TreeNode* pRootOfTree)
{
	if (nullptr == pRootOfTree)
		return nullptr;

	// 遍历左子树节点
	this->Convert(pRootOfTree->left);

	// 组成双向链表
	if (nullptr != pCur)
	{
		pPrev->right = pRootOfTree;
		pRootOfTree->left = pPrev;
	}
	else
		pCur = pRootOfTree;

	pPrev = pRootOfTree;

	// 遍历右子树节点
	this->Convert(pRootOfTree->right);
	return pCur;
}

void Convert_Solution::ConvertTest()
{
	TreeNode fst(1);
	TreeNode sec(2);
	TreeNode thr(3);
	TreeNode four(4);
	TreeNode five(5);
	TreeNode six(6);
	TreeNode seven(7);

	four.left = &sec;
	four.right = &six;

	sec.left = &fst;
	sec.right = &thr;

	six.left = &five;
	six.right = &seven;

	TreeNode* pCur = this->Convert(&four);
	while (nullptr != pCur) {
		cout << pCur->val << " ";
		pCur = pCur->right;
	}
	cout << endl;
}

TreeNode* mergeTrees_Solution::mergeTrees(TreeNode* t1, TreeNode* t2)
{
	if (nullptr == t1 && nullptr == t2)
		return nullptr;

	// 统计当前节点的数值
	int valSum = (nullptr != t1) ? t1->val : 0;
	valSum += (nullptr != t2) ? t2->val : 0;

	// 创建新节点
	TreeNode* newNode = new TreeNode(valSum);

	// 遍历节点左子树
	if (nullptr != t1 && nullptr != t2)
		newNode->left = this->mergeTrees(t1->left, t2->left);
	else if (nullptr == t1 && nullptr != t2)
		newNode->left = this->mergeTrees(nullptr, t2->left);
	else
		newNode->left = this->mergeTrees(t1->left, nullptr);

	// 遍历节点右子树
	if (nullptr != t1 && nullptr != t2)
		newNode->right = this->mergeTrees(t1->right, t2->right);
	else if (nullptr == t1 && nullptr != t2)
		newNode->right = this->mergeTrees(nullptr, t2->right);
	else
		newNode->right = this->mergeTrees(t1->right, nullptr);

	// 返回新节点
	return newNode;
}

void mergeTrees_Solution::mergeTreesTest()
{
	TreeNode fst_one(7);
	TreeNode fst_two(2);
	TreeNode fst_three(5);
	TreeNode fst_four(1);
	TreeNode fst_five(10);
	TreeNode fst_six(6);
	TreeNode fst_seven(6);
	TreeNode fst_eight(9);
	TreeNode fst_nineth(9);
	TreeNode fst_tenth(1);
	
	fst_one.left = &fst_two;
	fst_one.right = &fst_three;

	fst_two.left = &fst_four;

	fst_three.left = &fst_five;
	fst_three.right = &fst_six;

	fst_four.right = &fst_seven;

	
	fst_five.left = &fst_eight;
	fst_five.right = &fst_nineth;

	fst_seven.left = &fst_tenth;

	TreeNode sec_one(9);
	TreeNode sec_two(5);
	TreeNode sec_three(9);
	TreeNode sec_four(1);
	TreeNode sec_five(10);

	sec_one.left = &sec_two;
	sec_one.right = &sec_three;

	sec_three.left = &sec_four;
	sec_four.left = &sec_five;
	

	TreeNode* pCur = this->mergeTrees(&fst_one, &sec_one);
	this->preorder(pCur);
	this->recycle(pCur);
	cout << endl;
}

void mergeTrees_Solution::preorder(TreeNode* root)
{
	if (nullptr == root)
		return;

	cout << root->val << " ";
	this->preorder(root->left);
	this->preorder(root->right);
}

void mergeTrees_Solution::recycle(TreeNode* root)
{
	if (nullptr == root)
		return;

	this->recycle(root->left);
	this->recycle(root->right);
	delete root;
}

TreeNode* Mirror_Solution::Mirror(TreeNode* pRoot)
{
	if (nullptr == pRoot)
		return nullptr;

	if (nullptr == pRoot->left && nullptr != pRoot->right)
	{
		pRoot->left = pRoot->right;
		pRoot->right = nullptr;
	}
	else if (nullptr == pRoot->right && nullptr != pRoot->left)
	{
		pRoot->right = pRoot->left;
		pRoot->left = nullptr;
	}
	else if (nullptr != pRoot->left && nullptr != pRoot->right)
	{
		TreeNode* pTemp = pRoot->left;
		pRoot->left = pRoot->right;
		pRoot->right = pTemp;
	}

	Mirror(pRoot->left);
	Mirror(pRoot->right);
	return pRoot;
}

void Mirror_Solution::MirrorTest()
{
	TreeNode fst(1);
	TreeNode sec(2);
	TreeNode thr(3);
	TreeNode four(4);
	TreeNode five(5);
	TreeNode six(6);
	TreeNode seven(7);

	fst.left = &sec;
	fst.right = &thr;
	sec.left = &four;
	sec.right = &five;
	thr.left = &six;
	thr.right = &seven;

	TreeNode* pCur = this->Mirror(&fst);
	preorder(pCur);
	cout << endl;
}

bool isValidBST_Solution::isValidBST(TreeNode* root) 
{
	//中序遍历，二叉搜索树按照中序遍历为依次递增
	if (nullptr == root)
		return true;

	// 递归遍历左子树
	if (!isValidBST(root->left))
		return false;

	// 判断前一个节点的值是否比当前节点的值大
	if (pre >= root->val)
		return false;
	else
		pre = root->val;

	// 递归遍历右子树
	if (!isValidBST(root->right))
		return false;

	// 满足二叉搜索树条件
	return true;
}

void isValidBST_Solution::isValidBSTTest()
{
	TreeNode fst(4);
	TreeNode sec(2);
	TreeNode thr(5);
	TreeNode four(1);
	TreeNode five(3);

	fst.left = &sec;
	fst.right = &thr;
	sec.left = &four;
	sec.right = &five;

	bool res = this->isValidBST(&fst);
	cout << res << endl;
}

bool isCompleteTree_Solution::isCompleteTree(TreeNode* root)
{
	if (nullptr == root)
		return true;

	// 使用队列对完全二叉树进行层序遍历
	queue<TreeNode*> nodeQueue;
	nodeQueue.push(root);

	int endFlag = false;
	while (!nodeQueue.empty()) {
		TreeNode* pCur = nodeQueue.front();
		nodeQueue.pop();

		if (nullptr != pCur) {
			// 如果末尾标志位为true并且之后还有节点说明不是完全二叉树
			if (endFlag)
				return false;

			nodeQueue.push(pCur->left);
			nodeQueue.push(pCur->right);
		}
		else {
			// 遇到空节点将末尾标志位置为true
			if (!endFlag) {
				endFlag = true;
			}
		}
	}

	return true;
}

void isCompleteTree_Solution::isCompleteTreeTest()
{
	TreeNode fst(1);
	TreeNode sec(2);
	TreeNode thr(3);
	TreeNode four(4);
	TreeNode five(5);
	TreeNode six(6);
	TreeNode seven(7);

	fst.left = &sec;
	fst.right = &thr;
	sec.left = &four;
	sec.right = &five;
	thr.left = nullptr;
	thr.right = nullptr;

	bool res = this->isCompleteTree(&fst);
	cout << res << endl;
}

bool IsBalancedTree_Solution::IsBalancedTree(TreeNode* pRoot)
{
	if (nullptr == pRoot)
		return true;

	if (!this->IsBalancedTree(pRoot->left))
		return false;

	if (!this->IsBalancedTree(pRoot->right))
		return false;

	int leftLength = this->getTreeDepth(pRoot->left);
	int rightLength = this->getTreeDepth(pRoot->right);

	int diff = abs(leftLength - rightLength);
	return (diff <= 1) ? true : false;
}

int IsBalancedTree_Solution::getTreeDepth(TreeNode* pRoot)
{
	if (nullptr == pRoot)
		return 0;

	int leftLength = this->getTreeDepth(pRoot->left);
	int rightLength = this->getTreeDepth(pRoot->right);
	return (leftLength >= rightLength) ? ++leftLength : ++rightLength;
}

void IsBalancedTree_Solution::IsBalancedTreeTest()
{
	TreeNode fst(1);
	TreeNode sec(2);
	TreeNode thr(3);
	TreeNode four(4);
	TreeNode five(5);
	TreeNode six(6);

	fst.left = &sec;
	fst.right = &thr;
	sec.left = &four;
	thr.right = &five;
	four.left = &six;

	bool res = this->IsBalancedTree(&fst);
	cout << res << endl;
}

int lowestCommonAncestor_Solution::lowestCommonAncestor(TreeNode* root, int p, int q)
{
	if (nullptr == root)
		return -1;

	// 找到p或q节点
	if (p == root->val || q == root->val)
		return root->val;

	// 使用后序遍历对二叉树进行回溯
	int leftVal = this->lowestCommonAncestor(root->left, p, q);
	int rightVal = this->lowestCommonAncestor(root->right, p, q);

	if (-1 != leftVal && -1 != rightVal) {
		// 找到公共祖先
		return root->val;
	}
	else if (-1 != leftVal && -1 == rightVal) {
		// 找到p节点
		return leftVal;
	}
	else if (-1 == leftVal && -1 != rightVal) {
		// 找到q节点
		return rightVal;
	}
	else {
		// 不包含p或q节点
		return -1;
	}
}

void lowestCommonAncestor_Solution::lowestCommonAncestorTest()
{
	TreeNode fst(6);
	TreeNode sec(2);
	TreeNode thr(8);
	TreeNode four(0);
	TreeNode five(4);
	TreeNode six(7);
	TreeNode seven(9);
	TreeNode eight(3);
	TreeNode nine(5);

	fst.left = &sec;
	fst.right = &thr;
	sec.left = &four;
	sec.right = &five;
	thr.left = &six;
	thr.right = &seven;
	five.left = &eight;
	five.right = &nine;

	int res = this->lowestCommonAncestor(&fst, 3, 5);
	cout << res << endl;
}

char* Serialize_Solution::Serialize(TreeNode *root)
{
	if (nullptr == root)
		return nullptr;

	// 前序遍历二叉树
	stringstream ss;
	serialHelp(root, ss);

	// 返回二叉树节点序列化后的字符串
	char* sSerial = new char[ss.str().size() + 1];
	strcpy(sSerial, ss.str().c_str());
	return sSerial;
}

void Serialize_Solution::serialHelp(TreeNode *root, stringstream& ss)
{
	if (nullptr == root) {
		ss << '#' << ',';
	}
	else {
		ss << root->val << ',';
		serialHelp(root->left, ss);
		serialHelp(root->right, ss);
	}
}

TreeNode* Serialize_Solution::Deserialize(char *str)
{
	if (nullptr == str)
		return nullptr;

	// 拆解字符串进队列
	string numStr;
	queue<int> que;
	int length = strlen(str);
	for (int i = 0; i < length; ++i) {
		if (',' == str[i]) {
			if (!numStr.empty()) {
				que.push(atoi(numStr.c_str()));
				numStr.clear();
			}
		}
		else if ('#' == str[i]) {
			que.push(-1);
		}
		else {
			numStr.push_back(str[i]);
		}
	}

	// 递归组建二叉树
	return deSerialHelp(que);
}

TreeNode* Serialize_Solution::deSerialHelp(queue<int>& que)
{
	if (que.empty())
		return nullptr;

	int val = que.front();
	que.pop();

	// INT_MIN代表节点为nullptr
	if (-1 == val)
		return nullptr;

	TreeNode* root = new TreeNode(val);
	root->left = deSerialHelp(que);
	root->right = deSerialHelp(que);

	return root;
}

void Serialize_Solution::demo()
{
	TreeNode fst(1);
	TreeNode sec(2);
	TreeNode thr(3);
	TreeNode four(4);
	TreeNode five(5);
	TreeNode six(6);
	TreeNode seven(7);

	fst.left = &sec;
	fst.right = &thr;
	sec.left = &four;
	sec.right = &five;
	thr.left = &six;
	thr.right = &seven;

	char* str = this->Serialize(&fst);
	if (nullptr == str)
		cout << "NULL" << endl;
	else
		cout << str << endl;

	TreeNode* root = this->Deserialize(str);
	preorder(root);

	delete str;
	cycle(root);
}

TreeNode* reConstructBinaryTree_Solution::reConstructBinaryTree(vector<int>& preOrder, vector<int>& inOrder)
{
	TreeNode* root = this->reConstructHelp(preOrder, 0, preOrder.size() - 1, inOrder, 0, inOrder.size() - 1);
	return root;
}

TreeNode* reConstructBinaryTree_Solution::reConstructHelp(vector<int>& preOrder, int pStart, int pEnd, vector<int>& inOrder, int iStart, int iEnd)
{
	if (pStart > pEnd || iStart > iEnd)
		return nullptr;

	// 新增当前根节点
	TreeNode* root = new TreeNode(preOrder[pStart]);

	// 找到根节点的索引
	int rootIdx = 0;
	while (rootIdx <= iEnd) {
		if (root->val == inOrder[rootIdx])
			break;
		else
			++rootIdx;
	}

	// 确定前序数组左子树和右子树的范围
	int preLeftStartIdx = pStart + 1;
	int preLeftEndIdx = preLeftStartIdx + (rootIdx - iStart - 1);

	int preRightStartIdx = pStart + (rootIdx - iStart) + 1;
	int preRightEndIdx = pEnd;

	// 确定中序数组左子树和右子树的范围
	int inLeftStartIdx = iStart;
	int inLeftEndIdx = iStart + rootIdx - 1;

	int inRightStartIdx = rootIdx + 1;
	int inRightEndIdx = iEnd;

	// 根节点的左子树和右子树构建
	root->left = this->reConstructHelp(preOrder, preLeftStartIdx, preLeftEndIdx, inOrder, inLeftStartIdx, inLeftEndIdx);
	root->right = this->reConstructHelp(preOrder, preRightStartIdx, preRightEndIdx, inOrder, inRightStartIdx, inRightEndIdx);
	return root;
}

void reConstructBinaryTree_Solution::demo()
{
	vector<int> preOrder = initializer_list<int>{ 1, 2, 8, 4, 5, 6, 7, 3 };
	vector<int> inOrder = initializer_list<int>{ 8, 2, 1, 5, 7, 6, 4, 3 };

	TreeNode* root = this->reConstructBinaryTree(preOrder, inOrder);
	preorder(root);

	cycle(root);
}

vector<int> solve_Solution::solve(vector<int>& preOrder, vector<int>& inOrder)
{
	vector<int> rightView;
	if (preOrder.empty() || inOrder.empty())
		return rightView;

	TreeNode* root = this->buildTree(preOrder, 0, preOrder.size() - 1, inOrder, 0, inOrder.size() - 1);
	preorder(root);

	this->getTreeRightView(root, rightView);
	return rightView;
}

TreeNode* solve_Solution::buildTree(vector<int>& preOrder, int pStart, int pEnd, vector<int>& inOrder, int iStart, int iEnd)
{
	if (pStart > pEnd || iStart > iEnd)
		return nullptr;

	// 创建新节点
	TreeNode* newNode = new TreeNode(preOrder[pStart]);

	// 查找新节点在中序遍历数组的位置
	int idx = 0;
	for (int i = iStart; i <= iEnd; ++i) {
		if (newNode->val == inOrder[i]) {
			idx = i;
			break;
		}
	}

	// 新节点的左右子树赋值
	newNode->left = this->buildTree(preOrder, pStart + 1, pStart + (idx - iStart), inOrder, iStart, idx - 1);
	newNode->right = this->buildTree(preOrder, pStart + (idx - iStart) + 1, pEnd, inOrder, idx + 1, iEnd);
	return newNode;
}

void solve_Solution::getTreeRightView(TreeNode* root, vector<int>& rightView)
{
	if (nullptr == root)
		return;

	// 使用层序遍历找到二叉树每层的最右边节点
	queue<TreeNode*> nodeQue;
	nodeQue.push(root);
	while (!nodeQue.empty()) {
		int curQueSize = nodeQue.size();
		for (int i = 0; i < curQueSize; ++i) {
			TreeNode* node = nodeQue.front();
			nodeQue.pop();

			if(nullptr != node->left)
				nodeQue.push(node->left);

			if (nullptr != node->right)
				nodeQue.push(node->right);

			if (curQueSize - 1 == i) {
				rightView.push_back(node->val);
				break;
			}
		}
	}
}

void solve_Solution::demo()
{
	vector<int> preOrder = initializer_list<int>{ 1, 2, 8, 4, 5, 6, 7, 3 };
	vector<int> inOrder = initializer_list<int>{ 8, 2, 1, 5, 7, 6, 4, 3 };

	vector<int> rightView = this->solve(preOrder, inOrder);
	std::for_each(rightView.begin(), rightView.end(), [](int val) {
		cout << val << " ";
		});
	cout << endl;
}