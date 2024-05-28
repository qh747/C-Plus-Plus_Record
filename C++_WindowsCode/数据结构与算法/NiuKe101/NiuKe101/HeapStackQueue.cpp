#include "HeapStackQueue.h"

void TwoStackImplQueue_Solution::push(int node)
{
	stack1.push(node);
}

int TwoStackImplQueue_Solution::pop()
{
	// 两个栈都为空, 没有数据
	if (stack1.empty() && stack2.empty())
		return -1;

	// 弹出栈为空，从插入栈获取数据
	int node = 0;
	if (stack2.empty()) {
		while (!stack1.empty()) {
			node = stack1.top();
			stack1.pop();

			stack2.push(node);
		}
	}

	// 从弹出栈取出数据
	node = stack2.top();
	stack2.pop();
	return node;
}

void TwoStackImplQueue_Solution::demo()
{
	for (int i = 0; i < 10; ++i) {
		this->push(i);
	}

	int val = this->pop();
	while (-1 != val) {
		cout << val << " ";
		val = this->pop();
	}
	cout << endl;
}

void IncludeMinStack_Solution::push(int value)
{
	m_dataStack.push(value);

	// 存储最小元素的栈中元素个数与存储数据元素的栈中元素个数相同
	if (m_minStack.empty() || m_minStack.top() > value)
		m_minStack.push(value);
	else
		m_minStack.push(m_minStack.top());
}

void IncludeMinStack_Solution::pop()
{
	// 存储最小元素的栈中元素个数与存储数据元素的栈中元素个数相同
	m_dataStack.pop();
	m_minStack.pop();
}

int IncludeMinStack_Solution::top()
{
	return m_dataStack.top();
}

int IncludeMinStack_Solution::min()
{
	return m_minStack.top();
}

void IncludeMinStack_Solution::demo()
{
	// 元素入栈并显示最小元素
	for (int i = 0; i <= 10; ++i) {
		this->push(i);

		cout << "In Push Motivation. Min Value: " << this->min() << " Top Value: " << this->top() << endl;
	}

	// 元素出栈并显示最小元素
	for (int i = 0; i < 10; ++i) {
		this->pop();

		cout << "In Pop Motivation. Min Value: " << this->min() << " Top Value: " << this->top() << endl;
	}
}

bool isValid_Solution::isValid(string s)
{
	if (s.empty())
		return false;

	stack<char> cStack;
	for (int i = 0; i < s.size(); ++i) {
		if (']' == s[i] || ')' == s[i] || '}' == s[i]) {
			if (cStack.empty())
				return false;

			char val = cStack.top();
			cStack.pop();

			if (')' == s[i] && '(' != val)
				return false;
			else if (']' == s[i] && '[' != val)
				return false;
			else if ('}' == s[i] && '{' != val)
				return false;
		}
		else
			cStack.push(s[i]);
	}

	if (cStack.empty())
		return true;
	else
		return false;
}

void isValid_Solution::demo()
{
	string s = "[](){}";
	cout << this->isValid(s) << endl;

	s = "{[()]}";
	cout << this->isValid(s) << endl;

	s = "{[({)]}";
	cout << this->isValid(s) << endl;
}