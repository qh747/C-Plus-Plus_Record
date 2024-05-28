#pragma once
#include <iostream>
#include <stack>
#include <string>
using std::cout;
using std::endl;
using std::stack;
using std::string;

// BM1 - 用两个栈实现队列
class TwoStackImplQueue_Solution
{
public:
	void push(int node);
	int pop();

public:
	void demo();

private:
	stack<int> stack1;
	stack<int> stack2;
};

// BM2 - 包含min函数的栈
class IncludeMinStack_Solution 
{
public:
	void push(int value);
	void pop();
	int top();
	int min();

public:
	void demo();

private:
	stack<int> m_dataStack;
	stack<int> m_minStack;
};

// BM3 - 有效括号序列
class isValid_Solution {
public:
	bool isValid(string s);
	void demo();
};