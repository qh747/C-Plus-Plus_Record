#include "PriorityQueue.h"

void BigTopPriorityQueue::push(int val)
{
	m_queue.push_back(val);
	this->adjust();
}

int BigTopPriorityQueue::top()
{
	try {
		if (m_queue.empty()) {
			throw "Queue Is Empty. Get Top Value Error";
		}		
		else {
			return m_queue[0];
		}
	}
	catch (const string& err) {
		cerr << err << endl;
	}
}

void BigTopPriorityQueue::pop()
{
	try {
		if (m_queue.empty()) {
			throw "Queue Is Empty. Get Top Value Error";
		}
		else {
			// 调换第一个元素和最后一个元素的顺序，减少数组移动的消耗
			swap(m_queue[0], m_queue[m_queue.size() - 1]);
			m_queue.erase(--m_queue.end());
			this->adjust();
		}
	}
	catch (const string& err) {
		cerr << err << endl;
	}
}

void BigTopPriorityQueue::adjust()
{
	// 一次获取数组索引，多次使用
	int size = m_queue.size();

	int lastNotLeafNodeIdx = (size / 2) - 1;
	for (int i = lastNotLeafNodeIdx; i >= 0; --i) {
		int curLeftChildIdx = 2 * i + 1;

		// 左孩子节点索引在数组有效范围并且左孩子节点大于当前节点
		if (curLeftChildIdx >= 0 && curLeftChildIdx < size && m_queue[curLeftChildIdx] > m_queue[i]) {
			swap(m_queue[i], m_queue[curLeftChildIdx]);
			
			// 递归调整
			this->adjust();
		}

		int curRightChildIdx = 2 * i + 2;
		// 右孩子节点索引在数组有效范围并且右孩子节点大于当前节点
		if (curRightChildIdx >= 0 && curRightChildIdx < size && m_queue[curRightChildIdx] > m_queue[i]) {
			swap(m_queue[i], m_queue[curRightChildIdx]);

			// 递归调整
			this->adjust();
		}
	}
}

void SmallTopPriorityQueue::push(int val)
{
	m_queue.push_back(val);
	this->adjust();
}

int SmallTopPriorityQueue::top()
{
	try {
		if (m_queue.empty()) {
			throw "Queue Is Empty. Get Top Value Error";
		}
		else {
			return m_queue[0];
		}
	}
	catch (const string& err) {
		cerr << err << endl;
	}
}

void SmallTopPriorityQueue::pop()
{
	try {
		if (m_queue.empty()) {
			throw "Queue Is Empty. Get Top Value Error";
		}
		else {
			// 调换第一个元素和最后一个元素的顺序，减少数组移动的消耗
			swap(m_queue[0], m_queue[m_queue.size() - 1]);
			m_queue.erase(--m_queue.end());
			this->adjust();
		}
	}
	catch (const string& err) {
		cerr << err << endl;
	}
}

void SmallTopPriorityQueue::adjust()
{
	// 一次获取数组索引，多次使用
	int size = m_queue.size();

	int lastNotLeafNodeIdx = (size / 2) - 1;
	for (int i = lastNotLeafNodeIdx; i >= 0; --i) {
		int curLeftChildIdx = 2 * i + 1;

		// 左孩子节点索引在数组有效范围并且左孩子节点小于当前节点
		if (curLeftChildIdx >= 0 && curLeftChildIdx < size && m_queue[curLeftChildIdx] < m_queue[i]) {
			swap(m_queue[i], m_queue[curLeftChildIdx]);

			// 递归调整
			this->adjust();
		}

		int curRightChildIdx = 2 * i + 2;
		// 右孩子节点索引在数组有效范围并且右孩子节点小于当前节点
		if (curRightChildIdx >= 0 && curRightChildIdx < size && m_queue[curRightChildIdx] < m_queue[i]) {
			swap(m_queue[i], m_queue[curRightChildIdx]);

			// 递归调整
			this->adjust();
		}
	}
}