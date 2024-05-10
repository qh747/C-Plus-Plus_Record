#include "DataStructTest.h"
#define DATASTRUCT_TEST_SEQ  8

/*数据结构测试																**/
void dataStructTest()
{
#if 1 == DATASTRUCT_TEST_SEQ

	/*动态数组测试															**/
	funcDynamicArrayTest();

#elif 2 == DATASTRUCT_TEST_SEQ

	/*改进版动态数组测试													**/
	funcDynamicArrayAdvTest();
	
#elif 3 == DATASTRUCT_TEST_SEQ

	/*单向链表测试															**/
	funcSingleLinkListTest();

#elif 4 == DATASTRUCT_TEST_SEQ

	/*双向链表测试															**/
	funcDoubleLinkListTest();

#elif 5 == DATASTRUCT_TEST_SEQ

	/*顺序栈测试															**/
	funcSequenceStackTest();

#elif 6 == DATASTRUCT_TEST_SEQ

	/*链式栈测试															**/
	funcLinkStackTest();

#elif 7 == DATASTRUCT_TEST_SEQ

	/*顺序队列测试															**/
	funcSequenceQueueTest();

#elif 8 == DATASTRUCT_TEST_SEQ

	/*二叉树测试															**/
	funcBinaryTreeTest();

#endif
}

/*动态数组测试																**/
void funcDynamicArrayTest()
{
	DynamicArray dyncArray;

	/*添加数据测试															**/
	for (int i = 1; i <= 10; ++i)
	{
		dyncArray.addVal(i);
	}

	cout << "ADD DATA TEST." << endl << "Dynamic Array: ";
	for (int i = 0; i < dyncArray.getSize(); ++i)
	{
		cout << dyncArray.getVal(i) << " ";
	}
	cout << endl << "Capacity: " << dyncArray.getCapacity() << endl;
	cout <<  "Size: " << dyncArray.getSize() << endl << endl;


	/*插入数据测试															**/
	dyncArray.insertVal(0, 0);
	dyncArray.insertVal(dyncArray.getSize(), 11);

	cout  << endl << "INSERT DATA TEST." << endl << "Dynamic Array: ";
	for (int i = 0; i < dyncArray.getSize(); ++i)
	{
		cout << dyncArray.getVal(i) << " ";
	}
	cout << endl << "Capacity: " << dyncArray.getCapacity() << endl;
	cout << "Size: " << dyncArray.getSize() << endl << endl;


	/*修改数据测试															**/
	int curSize = dyncArray.getSize();
	for (int i = 0; i < curSize; ++i)
	{
		if (dyncArray.getVal(i) < 5)
			dyncArray.modifyVal(i, 0);
	}

	cout << endl << "MODIFY DATA TEST." << endl << "Dynamic Array: ";
	for (int i = 0; i < dyncArray.getSize(); ++i)
	{
		cout << dyncArray.getVal(i) << " ";
	}
	cout << endl << "Capacity: " << dyncArray.getCapacity() << endl;
	cout << "Size: " << dyncArray.getSize() << endl << endl;


	/*删除数据测试															**/
	while (true)
	{
		int delIndex = -1;
		for (int i = 0; i < dyncArray.getSize(); ++i)
		{
			if (0 == dyncArray.getVal(i))
			{
				delIndex = i;
				break;
			}	
		}

		if (-1 == delIndex)
			break;
		else
			dyncArray.delVal(delIndex);
	}

	cout << endl << "DELETE DATA TEST." << endl << "Dynamic Array: ";
	for (int i = 0; i < dyncArray.getSize(); ++i)
	{
		cout << dyncArray.getVal(i) << " ";
	}
	cout << endl << "Capacity: " << dyncArray.getCapacity() << endl;
	cout << "Size: " << dyncArray.getSize() << endl << endl;


	/*清空数据测试															**/
	dyncArray.clear();
	cout << endl << "DELETE DATA TEST." << endl << "Dynamic Array Size: " << dyncArray.getSize();
	cout << endl << "Capacity: " << dyncArray.getCapacity() << endl;
	cout << "Size: " << dyncArray.getSize() << endl;
}

/*改进版动态数组测试														**/
void funcDynamicArrayAdvTest()
{
	DynamicArrayAdv dyncAdvArray;

	/*添加数据测试															**/
	for (int i = 1; i <= 10; ++i)
	{
		dyncAdvArray.pushBack(i);
	}

	cout << "ADD DATA TEST." << endl << "Dynamic Array Adv: ";
	for (int i = 0; i < dyncAdvArray.size(); ++i)
	{
		cout << dyncAdvArray[i] << " ";
	}
	cout << endl << "Capacity: " << dyncAdvArray.capacity() << endl;
	cout << "Size: " << dyncAdvArray.size() << endl << endl;


	/*插入数据测试															**/
	dyncAdvArray.insert(0, 0);
	dyncAdvArray.insert(dyncAdvArray.size(), 11);

	cout << endl << "INSERT DATA TEST." << endl << "Dynamic Array: ";
	for (int i = 0; i < dyncAdvArray.size(); ++i)
	{
		cout << dyncAdvArray[i] << " ";
	}
	cout << endl << "Capacity: " << dyncAdvArray.capacity() << endl;
	cout << "Size: " << dyncAdvArray.size() << endl << endl;


	/*修改数据测试															**/
	int curSize = dyncAdvArray.size();
	for (int i = 0; i < curSize; ++i)
	{
		if (dyncAdvArray[i] < 5)
			dyncAdvArray[i] = 0;
	}

	cout << endl << "MODIFY DATA TEST." << endl << "Dynamic Array: ";
	for (int i = 0; i < dyncAdvArray.size(); ++i)
	{
		cout << dyncAdvArray[i] << " ";
	}
	cout << endl << "Capacity: " << dyncAdvArray.capacity() << endl;
	cout << "Size: " << dyncAdvArray.size() << endl << endl;


	/*删除数据测试															**/
	while (true)
	{
		int delIndex = -1;
		for (int i = 0; i < dyncAdvArray.size(); ++i)
		{
			if (0 == dyncAdvArray[i])
			{
				delIndex = i;
				break;
			}
		}

		if (-1 == delIndex)
			break;
		else
			dyncAdvArray.erase(delIndex);
	}

	cout << endl << "DELETE DATA TEST." << endl << "Dynamic Array: ";
	for (int i = 0; i < dyncAdvArray.size(); ++i)
	{
		cout << dyncAdvArray[i] << " ";
	}
	cout << endl << "Capacity: " << dyncAdvArray.capacity() << endl;
	cout << "Size: " << dyncAdvArray.size() << endl << endl;


	/*清空数据测试															**/
	dyncAdvArray.clear();
	cout << endl << "DELETE DATA TEST." << endl << "Dynamic Array Size: " << dyncAdvArray.size();
	cout << endl << "Capacity: " << dyncAdvArray.capacity() << endl;
}

/*单向链表测试																**/
void funcSingleLinkListTest()
{
	SingleLinkList linkList;

	/*添加数据测试															**/
	for (int i = 4; i <= 6; ++i)
	{
		linkList.pushBack(i);
	}

	for (int i = 3; i >= 1; --i)
	{
		linkList.pushFront(i);
	}

	cout << "ADD DATA TEST." << endl << "Single Link Size: ";
	for (int i = 0; i < linkList.size(); ++i)
	{
		cout << linkList.at(i) << " ";
	}
	cout << endl << "Size: " << linkList.size() << endl << endl;


	/*插入数据测试															**/
	linkList.insert(0, 0);
	linkList.insert(linkList.size() / 2, 50);
	linkList.insert(linkList.size(), 100);

	cout << endl << "INSERT DATA TEST." << endl << "Single Link Size: ";
	for (int i = 0; i < linkList.size(); ++i)
	{
		cout << linkList.at(i) << " ";
	}
	cout << endl << "Size: " << linkList.size() << endl << endl;


	/*修改数据测试															**/
	int curSize = linkList.size();
	for (int i = 0; i < curSize; ++i)
	{
		if (linkList.at(i) < 5)
			linkList.at(i) = 0;
	}

	cout << endl << "MODIFY DATA TEST." << endl << "Single Link Size: ";
	for (int i = 0; i < linkList.size(); ++i)
	{
		cout << linkList.at(i) << " ";
	}
	cout << endl << "Size: " << linkList.size() << endl << endl;


	/*删除数据测试															**/
	while (true)
	{
		int delIndex = -1;
		for (int i = 0; i < linkList.size(); ++i)
		{
			if (0 == linkList.at(i))
			{
				delIndex = i;
				break;
			}
		}

		if (-1 == delIndex)
			break;
		else
			linkList.erase(delIndex);
	}

	cout << endl << "DELETE DATA TEST." << endl << "Single Link Size: ";
	for (int i = 0; i < linkList.size(); ++i)
	{
		cout << linkList.at(i) << " ";
	}
	cout << endl << "Size: " << linkList.size() << endl << endl;


	/*清空数据测试															**/
	linkList.clear();
	cout << endl << "CLEAR DATA TEST." << endl << "Single Link Size: " << linkList.size() << endl;
}

/*双向链表测试																**/
void funcDoubleLinkListTest()
{
	DoubleLinkList linkList;

	/*添加数据测试															**/
	for (int i = 4; i <= 6; ++i)
	{
		linkList.pushBack(i);
	}

	for (int i = 3; i >= 1; --i)
	{
		linkList.pushFront(i);
	}

	cout << "ADD DATA TEST." << endl << "Double Link Size: ";
	for (int i = 0; i < linkList.size(); ++i)
	{
		cout << linkList.at(i) << " ";
	}
	cout << endl << "Size: " << linkList.size() << endl << endl;


	///*插入数据测试															**/
	linkList.insert(0, 0);
	linkList.insert(linkList.size() / 2, 50);
	linkList.insert(linkList.size(), 100);

	cout << endl << "INSERT DATA TEST." << endl << "Double Link Size: ";
	for (int i = 0; i < linkList.size(); ++i)
	{
		cout << linkList.at(i) << " ";
	}
	cout << endl << "Size: " << linkList.size() << endl << endl;


	/*修改数据测试																**/
	int curSize = linkList.size();
	for (int i = 0; i < curSize; ++i)
	{
		if (linkList.at(i) < 5)
			linkList.at(i) = 0;
	}

	cout << endl << "MODIFY DATA TEST." << endl << "Double Link Size: ";
	for (int i = 0; i < linkList.size(); ++i)
	{
		cout << linkList.at(i) << " ";
	}
	cout << endl << "Size: " << linkList.size() << endl << endl;


	/*删除数据测试																**/
	while (true)
	{
		int delIndex = -1;
		for (int i = 0; i < linkList.size(); ++i)
		{
			if (0 == linkList.at(i))
			{
				delIndex = i;
				break;
			}
		}

		if (-1 == delIndex)
			break;
		else
			linkList.erase(delIndex);
	}

	cout << endl << "DELETE DATA TEST." << endl << "Double Link Size: ";
	for (int i = 0; i < linkList.size(); ++i)
	{
		cout << linkList.at(i) << " ";
	}
	cout << endl << "Size: " << linkList.size() << endl << endl;


	/*清空数据测试																**/
	linkList.clear();
	cout << endl << "CLEAR DATA TEST." << endl << "Double Link Size: " << linkList.size() << endl;
}

/*顺序栈测试																**/
void funcSequenceStackTest()
{
	SequenceStack fstSeqStack;

	cout << "First Stack Push: ";
	for (int i = 1; i <= 10; ++i)
	{
		fstSeqStack.push(i);
		cout << i << " ";
	}
	cout << endl << endl;

	cout << "First Stack Size: " << fstSeqStack.size() << endl << endl;

	cout << "First Stack Pop: ";
	while (!fstSeqStack.empty())
	{
		int topVal = fstSeqStack.top();
		fstSeqStack.pop();

		cout <<  topVal << " ";
	}
	cout << endl << endl;

	SequenceStack secSeqStack(10);

	cout << "Second Stack Push: ";
	for (int i = 11; i <= 21; ++i)
	{
		secSeqStack.push(i);
		cout << i << " ";
	}
	cout << endl << endl;

	cout << "Second Stack Size: " << secSeqStack.size() << endl << endl;

	cout << "Second Stack Pop: ";
	while (!secSeqStack.empty())
	{
		int topVal = secSeqStack.top();
		secSeqStack.pop();

		cout << topVal << " ";
	}
	cout << endl << endl;
}

/*链式栈测试																**/
void funcLinkStackTest()
{
	LinkStack fstLinkStack;

	cout << "First Stack Push: ";
	for (int i = 1; i <= 10; ++i)
	{
		fstLinkStack.push(i);
		cout << i << " ";
	}
	cout << endl << endl;

	cout << "First Stack Size: " << fstLinkStack.size() << endl << endl;

	cout << "First Stack Pop: ";
	while (!fstLinkStack.empty())
	{
		int topVal = fstLinkStack.top();
		fstLinkStack.pop();

		cout << topVal << " ";
	}
	cout << endl << endl;

	LinkStack secLinkStack(10);

	cout << "Second Stack Push: ";
	for (int i = 11; i <= 21; ++i)
	{
		secLinkStack.push(i);
		cout << i << " ";
	}
	cout << endl << endl;

	cout << "Second Stack Size: " << secLinkStack.size() << endl << endl;

	cout << "Second Stack Pop: ";
	while (!secLinkStack.empty())
	{
		int topVal = secLinkStack.top();
		secLinkStack.pop();

		cout << topVal << " ";
	}
	cout << endl << endl;
}

/*顺序队列测试																**/
void funcSequenceQueueTest()
{
	SequenceQueue fstSeqQueue;

	cout << "First Queue Push: ";
	for (int i = 1; i <= 10; ++i)
	{
		fstSeqQueue.push(i);
		cout << i << " ";
	}
	cout << endl << endl;

	cout << "First Queue Size: " << fstSeqQueue.size() << endl << endl;

	cout << "First Queue Pop: ";
	while (!fstSeqQueue.empty())
	{
		int topVal = fstSeqQueue.top();
		fstSeqQueue.pop();

		cout << topVal << " ";
	}
	cout << endl << endl;

	SequenceQueue secSeqQueue(10);

	cout << "Second Queue Push: ";
	for (int i = 11; i <= 21; ++i)
	{
		secSeqQueue.push(i);
		cout << i << " ";
	}
	cout << endl << endl;

	cout << "Second Queue Size: " << secSeqQueue.size() << endl << endl;

	cout << "Second Queue Pop: ";
	while (!secSeqQueue.empty())
	{
		int topVal = secSeqQueue.top();
		secSeqQueue.pop();

		cout << topVal << " ";
	}
	cout << endl << endl;
}

/*二叉树测试																**/
void funcBinaryTreeTest()
{
	BinaryTree bTree;
	cout << "First Binary Tree Node Count: " << bTree.getNodeCount() << endl;
	cout << "First Binary Tree Leaf Node Count: " << bTree.getLeafNodeCount() << endl;
	cout << "First Binary Tree Depth: " << bTree.getTreeDepth() << endl;

	bTree.addNewNode(1);
	bTree.addNewNode(2);
	bTree.addNewNode(3);
	bTree.addNewNode(4);
	bTree.addNewNode(5);
	bTree.addNewNode(6);
	bTree.addNewNode(7);

	bTree.foreachTree(FIRST_SEQ_FOREACH);
	cout << "First Binary Tree Node Count: " << bTree.getNodeCount() << endl;
	cout << "First Binary Tree Leaf Node Count: " << bTree.getLeafNodeCount() << endl;
	cout << "First Binary Tree Depth: " << bTree.getTreeDepth() << endl << endl;

	BinaryTree* pCopyBTree = bTree.copyBinaryTree();
	pCopyBTree->foreachTree(MIDDLE_SEQ_FOREACH);
	cout << "Second Binary Tree Node Count: " << pCopyBTree->getNodeCount() << endl;
	cout << "Second Binary Tree Leaf Node Count: " << pCopyBTree->getLeafNodeCount() << endl;
	cout << "Second Binary Tree Depth: " << pCopyBTree->getTreeDepth() << endl << endl;

	BinaryTree* pSecCopyBTree = pCopyBTree->copyBinaryTree();
	pSecCopyBTree->foreachTree(LAST_SEQ_FOREACH);
	cout << "Third Binary Tree Node Count: " << pSecCopyBTree->getNodeCount() << endl;
	cout << "Third Binary Tree Leaf Node Count: " << pSecCopyBTree->getLeafNodeCount() << endl;
	cout << "Third Binary Tree Depth: " << pSecCopyBTree->getTreeDepth() << endl << endl;

	pSecCopyBTree->foreachTree(NON_RECURSION_FOREACH);
	pSecCopyBTree->foreachTree(HIERARCHICAL_FOREACH);

	delete pCopyBTree;
	delete pSecCopyBTree;
}