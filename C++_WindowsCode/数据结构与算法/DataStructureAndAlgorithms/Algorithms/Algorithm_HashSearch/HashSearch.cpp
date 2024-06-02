#include "HashSearch.h"

HashTable::HashTable(int primeNum, int rebuildDeepth)
{ 
	m_size = 0;
	m_primeNum = primeNum; 
	m_nodeVec.resize(m_primeNum);
	m_rebuildHashDeepth = rebuildDeepth;
}

HashTable::~HashTable()
{
	this->destoryHashTable();
}

void HashTable::insert(int val)
{
	int index = val % m_primeNum;
	if (nullptr == m_nodeVec[index]) {
		// 当前哈希表槽位未被使用
		m_nodeVec[index] = new HashNode_dt(index, val);
		++m_size;
	}
	else {
		// 当前哈希表槽位被使用
		HashNode_dt* pHead = m_nodeVec[index];

		// 查找链表末尾
		while (nullptr != pHead->pNext) {
			pHead = pHead->pNext;
		}
		pHead->pNext = new HashNode_dt(index, val);
		++m_size;
	}
}

bool HashTable::erase(int val)
{
	int index = val % m_primeNum;
	if (nullptr == m_nodeVec[index]) {
		// 当前哈希表槽位未被使用
		return false;
	}
	else {
		// 当前哈希表槽位被使用
		HashNode_dt* pHead = m_nodeVec[index];
		if (val == m_nodeVec[index]->iValue) {
			m_nodeVec[index] = pHead->pNext;
			delete pHead;
			--m_size;
			return true;
		}
		else {
			HashNode_dt* pPrev = pHead;
			pHead = pHead->pNext;

			// 查找val所在节点
			while (nullptr != pHead && val != pHead->iValue) {
				pPrev = pHead;
				pHead = pHead->pNext;
			}

			if (nullptr != pHead) {
				pPrev->pNext = pHead->pNext;
				delete pHead;
				--m_size;
				return true;
			}
			else {
				return false;
			}
		}
	}
}

void HashTable::modify(int oldVal, int newVal)
{
	this->erase(oldVal);
	this->insert(newVal);
}

bool HashTable::search(int val)
{
	int index = val % m_primeNum;
	if (nullptr == m_nodeVec[index]) {
		// 当前哈希表槽位未被使用
		return false;
	}
	else {
		// 当前哈希表槽位被使用
		HashNode_dt* pHead = m_nodeVec[index];

		// 查找val所在节点
		int count = 0;
		while (nullptr != pHead && val != pHead->iValue) {
			pHead = pHead->pNext;
			++count;
		}

		// 槽位中的链表深度过深
		if (count >= m_rebuildHashDeepth)
			this->rebuildHashTable();

		return (nullptr != pHead) ? true : false;
	}
}

void HashTable::destoryHashTable()
{
	for (int i = 0; i < m_nodeVec.size(); ++i) {
		if (nullptr == m_nodeVec[i])
			continue;

		// 链表销毁
		HashNode_dt* pHead = m_nodeVec[i];
		HashNode_dt* pNext = pHead->pNext;
		while (nullptr != pHead) {
			delete pHead;
			pHead = pNext;
			pNext = (nullptr != pNext) ? pNext->pNext : nullptr;
		}

		// 置空节点
		m_nodeVec[i] = nullptr;
	}
}

void HashTable::rebuildHashTable()
{
	// 使用新节点数组存储哈希节点
	vector<HashNode_dt*> newNodeVec;
	for (int i = 0; i < m_nodeVec.size(); ++i) {
		if (nullptr == m_nodeVec[i])
			continue;

		HashNode_dt* pHead = m_nodeVec[i];
		while (nullptr != pHead) {
			newNodeVec.push_back(pHead);
			pHead = pHead->pNext;
		}
	}
	m_nodeVec.clear();

	// 获取新质数
	m_primeNum = this->calcBiggerPrimeNum();
	m_nodeVec.resize(m_primeNum);

	// 重新计算节点索引
	for (int i = 0; i < newNodeVec.size(); ++i) {
		// 清空节点哈希标识
		HashNode_dt* node = newNodeVec[i];
		node->iIndex = node->iValue % m_primeNum;
		node->pNext = nullptr;

		// 重新加入哈希表
		HashNode_dt* pHead = m_nodeVec[node->iIndex];
		if (nullptr == pHead) {
			// 槽位为空
			m_nodeVec[node->iIndex] = node;
		}
		else {
			// 槽位不为空, 找链表末尾
			while (nullptr != pHead->pNext) {
				pHead = pHead->pNext;
			}
			pHead->pNext = node;
		}
	}
}

int HashTable::calcBiggerPrimeNum()
{
	for (int i = m_primeNum + 1; i < INT_MAX; ++i) {
		if (this->isPrime(i))
			return i;
	}
}

bool HashTable::isPrime(int num)
{
	// 小于等于1的数不是质数
	if (num <= 1) 
		return false; 

	// 2和3是质数
	if (num <= 3) 
		return true;  

	// 排除所有可被2或3整除的数
	if (num % 2 == 0 || num % 3 == 0) 
		return false;

	// 对于大于3的数，我们只检查到sqrt(num)即可
	for (int i = 5; i * i <= num; i += 6) {
		if (num % i == 0 || num % (i + 2) == 0)
			return false;
	}
	return true;
}

void funcHashSearch()
{
	vector<int> valVec = initializer_list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 28, 41, 54, 67, 80 };
	
	HashTable hashTable;
	for (int i = 0; i < valVec.size(); ++i) {
		hashTable.insert(valVec[i]);
	}

	cout << "Search: ";
	for (int i = 0; i < valVec.size(); ++i) {
		if (hashTable.search(valVec[i])) {
			cout << valVec[i] << " ";
		}
	}
	cout << endl << endl;

	cout << "Modify: ";
	srand(time(nullptr));
	for (int i = 0; i < valVec.size(); ++i) {
		hashTable.modify(valVec[i], rand() % 100);
	}

	cout << "Search After Modify: ";
	for (int i = 0; i <= 20; ++i) {
		if (hashTable.search(i)) {
			cout << i << " ";
		}
	}
	cout << endl << endl;

	cout << "Erase: ";
	for (int i = 0; i <= 100; ++i) {
		bool res = hashTable.erase(i);
		while (true == res) {
			res = hashTable.erase(i);
		}
		
	}

	cout << "Size: " << hashTable.size() << endl;
}