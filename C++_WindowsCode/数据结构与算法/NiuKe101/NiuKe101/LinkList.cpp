#include "LinkList.h"

ListNode* ReverseLinkList_Solution::ReverseList(ListNode* head)
{
	if (nullptr == head)
		return nullptr;
	if (nullptr == head->next)
		return head;

	ListNode* pPrev = nullptr;
	ListNode* pCur = head;
	ListNode* pNex = head->next;

	while (true)
	{
		pCur->next = pPrev;

		pPrev = pCur;
		pCur = pNex;
		pNex = pNex->next;

		if (nullptr == pNex)
		{
			pCur->next = pPrev;
			return pCur;
		}
	}
}

void ReverseLinkList_Solution::ReverseListTest()
{
	ListNode nodeFst(1);
	ListNode nodeSec(2);
	ListNode nodeThr(3);
	ListNode nodeFor(4);
	ListNode nodeFif(5);

	nodeFst.next = &nodeSec;
	nodeSec.next = &nodeThr;
	nodeThr.next = &nodeFor;
	nodeFor.next = &nodeFif;

	ListNode* pShowNode = &nodeFst;
	while (nullptr != pShowNode)
	{
		cout << pShowNode->val << " ";
		pShowNode = pShowNode->next;
	}
	cout << endl;

	ReverseLinkList_Solution solu;
	ListNode* pReverseHead = solu.ReverseList(&nodeFst);

	while (nullptr != pReverseHead)
	{
		cout << pReverseHead->val << " ";
		pReverseHead = pReverseHead->next;
	}
	cout << endl;
}

ListNode* ReverseBetween_Solution::reverseBetween(ListNode* head, int m, int n)
{
	if (nullptr == head)
		return nullptr;
	if (nullptr == head->next)
		return head;

	ListNode headPrev(-1);
	headPrev.next = head;

	ListNode* pPrev = &headPrev;
	ListNode* pCur = head;
	for (int i = 1; i < m; ++i)
	{
		pPrev = pCur;
		pCur = pCur->next;
	}

	for (int i = m; i < n; ++i)
	{
		ListNode* pNext = pCur->next;
		pCur->next = pNext->next;
		pNext->next = pPrev->next;
		pPrev->next = pNext;
	}

	return headPrev.next;
}

void ReverseBetween_Solution::ReverseBetweenTest()
{
	ListNode nodeFst(1);
	ListNode nodeSec(2);
	ListNode nodeThr(3);
	ListNode nodeFor(4);
	ListNode nodeFif(5);

	nodeFst.next = &nodeSec;
	nodeSec.next = &nodeThr;
	nodeThr.next = &nodeFor;
	nodeFor.next = &nodeFif;

	ListNode* pShowNode = &nodeFst;
	while (nullptr != pShowNode)
	{
		cout << pShowNode->val << " ";
		pShowNode = pShowNode->next;
	}
	cout << endl;

	ReverseBetween_Solution solu;
	ListNode* pReverseHead = solu.reverseBetween(&nodeFst, 2, 4);

	while (nullptr != pReverseHead)
	{
		cout << pReverseHead->val << " ";
		pReverseHead = pReverseHead->next;
	}
	cout << endl;
}

ListNode* Merge_Solution::Merge(ListNode* pHead1, ListNode* pHead2)
{
	if (nullptr == pHead1)
		return pHead2;
	if (nullptr == pHead2)
		return pHead1;

	// 创建一个新的首节点
	ListNode* pNewHead = new ListNode(-1);
	ListNode* pCur = pNewHead;

	// 在循环中不断后移pHead1和pHead2，直到两个指针都到末尾
	while (nullptr != pHead1 || nullptr != pHead2)
	{
		if (nullptr == pHead1)
		{
			// pHead1为空说明第一个链表到末尾，只不断向后移动第二个链表
			pCur->next = pHead2;
			pHead2 = pHead2->next;
		}
		else if (nullptr == pHead2)
		{
			// pHead2为空说明第二个链表到末尾，只不断向后移动第一个链表
			pCur->next = pHead1;
			pHead1 = pHead1->next;
		}
		else if (pHead1->val <= pHead2->val)
		{
			// pHead1的值小于等于pHead2的值，向后移动pHead1指针
			pCur->next = pHead1;
			pHead1 = pHead1->next;
		}
		else
		{
			// pHead2的值小于等于pHead1的值，向后移动pHead2指针
			pCur->next = pHead2;
			pHead2 = pHead2->next;
		}

		// 当前指针向后移动
		pCur = pCur->next;
	}

	pCur = pNewHead->next;
	delete pNewHead;

	return pCur;
}

void Merge_Solution::MergeTest()
{
	ListNode nodeFst(1);
	ListNode nodeSec(2);
	ListNode nodeThr(3);
	ListNode nodeFor(1);
	ListNode nodeFif(2);
	ListNode nodeSix(3);

	nodeFst.next = &nodeSec;
	nodeSec.next = &nodeThr;

	nodeFor.next = &nodeFif;
	nodeFif.next = &nodeSix;

	Merge_Solution solu;

	ListNode* pMergeHead = solu.Merge(&nodeFst, &nodeFor);
	while (nullptr != pMergeHead)
	{
		cout << pMergeHead->val << " ";
		pMergeHead = pMergeHead->next;
	}
	cout << endl;
}

ListNode* mergeKLists_Solution::mergeKLists(vector<ListNode*>& lists)
{
	if (lists.empty())
		return nullptr;
	else if (1 == lists.size())
		return lists[0];
	else
		return deverseLists(lists, 0, lists.size() -1);
}

ListNode* mergeKLists_Solution::deverseLists(vector<ListNode*>& lists, int start, int end)
{
	if (start > end)
		return nullptr;
	else if (start == end)
		return lists[start];
	else
	{
		int mid = (start + end) / 2;
		return this->mergeLists(deverseLists(lists, start, mid), deverseLists(lists, mid + 1, end));
	}
}

ListNode* mergeKLists_Solution::mergeLists(ListNode* pHeadFst, ListNode* pHeadSec)
{
	if (nullptr == pHeadFst)
		return pHeadSec;
	else if (nullptr == pHeadSec)
		return pHeadFst;

	ListNode* pNewHead = new ListNode(-1);
	ListNode* pCur = pNewHead;
	while (nullptr != pHeadFst || nullptr != pHeadSec)
	{
		if (nullptr == pHeadFst)
		{
			pCur->next = pHeadSec;
			pCur = pCur->next;
			pHeadSec = pHeadSec->next;
		}
		else if(nullptr == pHeadSec)
		{
			pCur->next = pHeadFst;
			pCur = pCur->next;
			pHeadFst = pHeadFst->next;
		}
		else if (pHeadFst->val <= pHeadSec->val)
		{
			pCur->next = pHeadFst;
			pCur = pCur->next;
			pHeadFst = pHeadFst->next;
		}
		else
		{
			pCur->next = pHeadSec;
			pCur = pCur->next;
			pHeadSec = pHeadSec->next;
		}
	}

	pCur = pNewHead->next;
	delete pNewHead;
	return pCur;
}

void mergeKLists_Solution::mergeKListsTest()
{
	vector<ListNode*> lists;
	ListNode firstHead = ListNode(1);
	ListNode fstSec = ListNode(4);
	ListNode fstThr = ListNode(5);

	ListNode secondHead = ListNode(0);
	ListNode secSec = ListNode(2);

	firstHead.next = &fstSec;
	fstSec.next = &fstThr;
	lists.push_back(&firstHead);

	secondHead.next = &secSec;
	lists.push_back(&secondHead);

	mergeKLists_Solution solu;
	ListNode* pMergeHead = solu.mergeKLists(lists);

	while (nullptr != pMergeHead)
	{
		cout << pMergeHead->val << " ";
		pMergeHead = pMergeHead->next;
	}
	cout << endl;
}

bool HasCycle_Solution::hasCycle(ListNode *head)
{
	if (nullptr == head || nullptr == head->next)
		return false;

	ListNode* pFast = head;
	ListNode* pSlow = head;

	while (nullptr != pFast && nullptr != pFast->next)
	{
		// 慢指针一次走一步
		pSlow = pSlow->next;

		// 快指针一次走两步
		pFast = pFast->next->next;

		// 如果快慢指针相遇代表链表有环
		if (pSlow == pFast)
			return true;
	}
	return false;
}

void HasCycle_Solution::hasCycleTest()
{
	ListNode frist(1);
	ListNode second(2);
	
	frist.next = &second;

	bool res = this->hasCycle(&frist);
	if (res)
		cout << "Has Cycle" << endl;
	else
		cout << "None" << endl;
}

ListNode* EntryNodeOfLoop_Solution::EntryNodeOfLoop(ListNode* pHead)
{
	if (nullptr == pHead || nullptr == pHead->next)
		return nullptr;

	ListNode* pFast = pHead;
	ListNode* pSlow = pHead;

	// 通过快慢指针找链表环路
	while (nullptr != pFast && nullptr != pFast->next)
	{
		pSlow = pSlow->next;
		pFast = pFast->next->next;
		if (nullptr == pFast)
			break;
		else if (pSlow == pFast)
			break;
	}

	// 链表无环, 退出
	if (nullptr == pFast || nullptr == pFast->next)
		return nullptr;

	// 链表有环, 找环入口节点
	pFast = pHead;
	while (pFast != pSlow)
	{
		pFast = pFast->next;
		pSlow = pSlow->next;

		if (pFast == pSlow)
			break;
	}
	return pFast;
}

void EntryNodeOfLoop_Solution::EntryNodeOfLoopTest()
{
	ListNode frist(1);
	ListNode second(2);
	ListNode third(3);
	ListNode forth(4);
	ListNode fifth(5);

	frist.next = &second;
	second.next = &third;
	third.next = &forth;
	forth.next = &fifth;
	fifth.next = &third;

	ListNode* res = this->EntryNodeOfLoop(&frist);
	if (nullptr != res)
		cout << "Has Cycle " << res->val << endl;
	else
		cout << "None" << endl;
}

ListNode* FindKthToTail_Solution::FindKthToTail(ListNode* pHead, int k)
{
	if (nullptr == pHead)
		return nullptr;

	ListNode* pFront = pHead;
	ListNode* pTail = pHead;

	// 尾指针向后移动, 移动步长为k
	for (int i = 0; i < k; ++i)
	{
		pTail = pTail->next;
		if (nullptr == pTail)
		{
			if (i == k - 1)
			{
				// 此时k的大小与链表长度相等，直接返回首指针
				return pHead;
			}
			else
			{
				// 步长k超过链表长度, 返回null
				return nullptr;
			}
		}
	}

	// 头指针和尾指针间隔为k，当尾指针指向null时，头指针指向距离尾指针前k间距的节点
	while (nullptr != pTail)
	{
		pFront = pFront->next;
		pTail = pTail->next;
	}
	return pFront;
}

void FindKthToTail_Solution::FindKthToTailTest()
{
	ListNode frist(1);
	ListNode second(2);
	ListNode third(3);
	ListNode forth(4);
	ListNode fifth(5);

	frist.next = &second;
	second.next = &third;
	third.next = &forth;
	forth.next = &fifth;

	ListNode* res = this->FindKthToTail(&frist, 5);
	if (nullptr != res)
		cout << "Node: " << res->val << endl;
	else
		cout << "None" << endl;
}

ListNode* FindFirstCommonNode_Solution::FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2)
{
	if (nullptr == pHead1 || nullptr == pHead2)
		return nullptr;

	// 找到第一个链表的最后一个节点
	ListNode* pFstListTailNode = pHead1;
	while (nullptr != pFstListTailNode->next)
	{
		pFstListTailNode = pFstListTailNode->next;
	}

	// 让第一个链表形成环路，如果两个链表有公共节点则为环路的入口节点
	pFstListTailNode->next = pHead1;

	// 判断链表是否有环路
	ListNode* pSlow = pHead2;
	ListNode* pFast = pHead2;
	while (nullptr != pFast && nullptr != pFast->next)
	{
		pSlow = pSlow->next;
		pFast = pFast->next->next;
		if (pSlow == pFast)
			break;
	}

	// 无环路，说明无公共节点
	if (nullptr == pFast || nullptr == pFast->next)
		return nullptr;

	// 有环路，找到入口节点
	pFast = pHead2;
	while (pFast != pSlow)
	{
		pFast = pFast->next;
		pSlow = pSlow->next;
	}

	// 还原，断开第一个链表的环路
	pFstListTailNode->next = nullptr;
	return pFast;
}

void FindFirstCommonNode_Solution::FindKthToTailTest()
{
	ListNode frist(1);
	ListNode second(2);
	ListNode third(3);
	ListNode forth(4);
	ListNode fifth(5);
	ListNode sixth(6);
	ListNode seventh(7);

	frist.next = &second;
	second.next = &third;
	third.next = &sixth;
	sixth.next = &seventh;

	forth.next = &fifth;
	fifth.next = &sixth;

	ListNode* res = this->FindFirstCommonNode(&frist, &forth);
	if (nullptr != res)
		cout << "Node: " << res->val << endl;
	else
		cout << "None" << endl;
}

ListNode* addInList_Solution::addInList(ListNode* head1, ListNode* head2)
{
	if (nullptr == head1)
		return head2;
	else if (nullptr == head2)
		return head1;

	// 翻转两个链表
	head1 = this->reverseList(head1);
	head2 = this->reverseList(head2);

	// 创建新链表并根据计算结果创建节点
	ListNode* newhead = new ListNode(-1);
	int carry = 0;
	while (nullptr != head1 || nullptr != head2 || 0 != carry)
	{
		int res = carry;
		if (nullptr != head1)
		{
			res += head1->val;
			head1 = head1->next;
		}

		if (nullptr != head2)
		{
			res += head2->val;
			head2 = head2->next;
		}

		carry = res / 10;
		res = res % 10;
	
		ListNode* pTemp = new ListNode(res);
		pTemp->next = newhead->next;
		newhead->next = pTemp;
	}

	ListNode* pDel = newhead;
	newhead = newhead->next;
	delete pDel;
	return newhead;
}

ListNode* addInList_Solution::reverseList(ListNode* head)
{
	ListNode* pPrev = nullptr;
	ListNode* pCur = head;

	while (nullptr != pCur)
	{
		ListNode* pNext = pCur->next;
		pCur->next = pPrev;
		
		pPrev = pCur;
		pCur = pNext;
	}
	return pPrev;
}

void addInList_Solution::addInListTest()
{
	ListNode frist(9);
	ListNode second(3);
	ListNode third(7);
	ListNode sixth(6);
	ListNode seventh(3);

	frist.next = &second;
	second.next = &third;
	sixth.next = &seventh;

	ListNode* res = this->addInList(&frist, &sixth);
	if (nullptr != res)
	{
		ListNode* delNode = res;
		while (nullptr != delNode)
		{
			cout << "Node: " << res->val << endl;

			res = res->next;
			delete delNode;
			delNode = res;
		}
	}
	else
		cout << "None" << endl;
}

ListNode* sortInList_Solution::sortInList(ListNode* head)
{
	// 断开链表连接关系, 并存入数组
	vector<ListNode*> nodeVec;
	while (nullptr != head)
	{
		ListNode* pNext = head->next;
		head->next = nullptr;

		nodeVec.push_back(head);
		head = pNext;
	}

	// 使用归并排序对数组进行排序
	this->mergeSort(nodeVec, 0, nodeVec.size() - 1);

	// 排序后再次连接节点
	head = nodeVec[0];
	ListNode* pCur = head;
	for (int i = 1; i < nodeVec.size(); ++i)
	{
		pCur->next = nodeVec[i];
		pCur = pCur->next;
	}

	return head;
}

void sortInList_Solution::mergeSort(vector<ListNode*>& vec, int start, int end)
{
	if (start >= end)
		return;

	// 递归划分数组
	mergeSort(vec, start, (start + end) / 2);
	mergeSort(vec, (start + end) / 2 + 1, end);

	// 合并数组
	mergeAlg(vec, start, end);
}

void sortInList_Solution::mergeAlg(vector<ListNode*>& vec, int start, int end)
{
	int startPos = start;
	int midPos = (start + end) / 2;
	int endPos = midPos + 1;

	// 将数组以中间元素所在位置分为两段，对两端按元素大小一次存放进待排序数组中
	vector<ListNode*> sortVec;
	while (startPos <= midPos && endPos <= end)
	{
		if (vec[startPos]->val <= vec[endPos]->val)
		{
			sortVec.push_back(vec[startPos]);
			++startPos;
		}
		else
		{
			sortVec.push_back(vec[endPos]);
			++endPos;
		}
	}

	// 如果左半段还有元素则依次存入待排序数据
	while (startPos <= midPos)
	{
		sortVec.push_back(vec[startPos]);
		++startPos;
	}

	// 如果右半段还有元素则依次存入待排序数据
	while (endPos <= end)
	{
		sortVec.push_back(vec[endPos]);
		++endPos;
	}

	// 将待排序数组中的元素还原至源数组中
	for (int i = start, j = 0; i <= end; ++i, ++j)
	{
		vec[i] = sortVec[j];
	}
}

void sortInList_Solution::sortInListTest()
{
	ListNode frist(9);
	ListNode second(3);
	ListNode third(7);
	ListNode sixth(6);
	ListNode seventh(3);

	frist.next = &second;
	second.next = &third;
	third.next = &sixth;
	sixth.next = &seventh;

	ListNode* res = this->sortInList(&frist);
	while (nullptr != res)
	{
		cout << "Node: " << res->val << endl;
		res = res->next;
	}
}

bool isPail_Solution::isPail(ListNode* head)
{
	if (nullptr == head)
		return false;

	// 将链表存入数组中
	vector<ListNode*> vec;
	while (nullptr != head)
	{
		vec.push_back(head);
		head = head->next;
	}

	// 使用首指针和尾指针遍历数组，回文结构满足首尾指针在遍历过程中指向的元素相等
	vector<ListNode*>::iterator headIter = vec.begin();
	vector<ListNode*>::reverse_iterator tailIter = vec.rbegin();
	while ((*headIter) != (*tailIter))
	{
		// 非回文链表
		if ((*headIter)->val != (*tailIter)->val)
			return false;
		
		if (vec.end() == ++headIter)
			break;

		if (vec.rend() == ++tailIter)
			break;
	}

	// 回文链表
	return true;
}

void isPail_Solution::isPailTest()
{
	ListNode frist(-401261);
	ListNode second(-449050);
	ListNode third(-456674);
	ListNode sixth(-456674);
	ListNode seventh(-449050);
	ListNode eighth(-401261);

	frist.next = &second;
	second.next = &third;
	third.next = &sixth;
	sixth.next = &seventh;
	seventh.next = &eighth;

	bool res = this->isPail(&frist);
	cout << res << endl;
}

ListNode* oddEvenList_Solution::oddEvenList(ListNode* head)
{
	if (nullptr == head)
		return nullptr;

	// 定义单数、双数首节点指针
	ListNode* singleHead = head;
	ListNode* evenHead = head->next;
	if (nullptr == evenHead)
		return head;

	// 单数、双数首节点指针依次修改之后的节点为单数、双数节点
	ListNode* curSingle = singleHead;
	ListNode* curEven = evenHead;
	head = curEven->next;
	int i = 1;
	while (nullptr != head)
	{
		if (1 == (i % 2))
		{
			curSingle->next = head;
			curSingle = curSingle->next;
		}	
		else
		{
			curEven->next = head;
			curEven = curEven->next;
		}
		
		head = head->next;
		++i;
	}

	// 单数末尾节点指向双数节点的首节点
	curSingle->next = evenHead;

	// 双数末尾节点指向NULL
	curEven->next = nullptr;

	// 返回单数首节点
	return singleHead;
}

void oddEvenList_Solution::oddEvenListTest()
{
	ListNode frist(1);
	ListNode second(2);
	ListNode third(3);
	ListNode sixth(4);
	ListNode seventh(5);

	frist.next = &second;
	second.next = &third;
	third.next = &sixth;
	sixth.next = &seventh;

	ListNode* res = this->oddEvenList(&frist);
	while (nullptr != res)
	{
		cout << "Node: " << res->val << endl;
		res = res->next;
	}
}

ListNode* deleteDuplicates_Solution::deleteDuplicates(ListNode* head)
{
	if (nullptr == head)
		return nullptr;

	ListNode* pCur = head;
	ListNode* pNext = head->next;

	while (nullptr != pNext)
	{
		if (pCur->val == pNext->val)
		{
			// 如果当前指针的值和下一个指针的值相等就不断后移下一个指针
			while (nullptr != pNext && pCur->val == pNext->val)
			{
				pNext = pNext->next;
			}
		}

		pCur->next = pNext;
		pCur = pNext;

		if (nullptr != pNext)
			pNext = pNext->next;
	}

	return head;
}

void deleteDuplicates_Solution::deleteDuplicatesTest()
{
	ListNode frist(1);
	ListNode second(2);
	ListNode third(2);
	ListNode sixth(4);
	ListNode seventh(4);

	frist.next = &second;
	second.next = &third;
	third.next = &sixth;
	sixth.next = &seventh;

	ListNode* res = this->deleteDuplicates(&frist);
	while (nullptr != res)
	{
		cout << "Node: " << res->val << endl;
		res = res->next;
	}
}

ListNode* deleteDuplicatesII_Solution::deleteDuplicatesII(ListNode* head)
{
	if (nullptr == head)
		return nullptr;

	// 将链表节点存进数组中
	vector<ListNode*> vec;
	while (nullptr != head)
	{
		vec.push_back(head);
		head = head->next;
	}

	// 借助数组移除链表中值相等的节点
	vector<ListNode*>::iterator iter = vec.begin();
	while (vec.end() != iter)
	{
		// 获取当前节点和下一个节点
		vector<ListNode*>::iterator subIter = iter;
		++subIter;

		if (vec.end() != subIter && (*iter)->val == (*subIter)->val)
		{
			// 如果下一个节点和当前节点的值相等，则从当节点开始，移除所有值相等的节点
			int val = (*iter)->val;
			while (vec.end() != iter && (*iter)->val == val)
			{
				iter = vec.erase(iter);
			}
		}
		else
		{
			// 如果下一个节点和当前节点的值不等，则迭代器向后移动
			++iter;
		}		
	}

	// 将数组中剩余不重复的节点恢复成新链表结构
	ListNode* newHead = new ListNode(-1);
	head = newHead;
	iter = vec.begin();
	while (vec.end() != iter)
	{
		head->next = (*iter++);
		head = head->next;
	}
	head->next = nullptr;

	head = newHead->next;
	delete newHead;
	return head;
}

void deleteDuplicatesII_Solution::deleteDuplicatesIITest()
{
	ListNode frist(1);
	ListNode second(1);
	ListNode third(2);
	ListNode sixth(2);
	ListNode seventh(4);
	ListNode eighth(5);

	frist.next = &second;
	second.next = &third;
	third.next = &sixth;
	sixth.next = &seventh;
	seventh.next = &eighth;

	ListNode* res = this->deleteDuplicatesII(&frist);
	while (nullptr != res)
	{
		cout << "Node: " << res->val << endl;
		res = res->next;
	}
}