#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <deque>
#include <queue>
using std::cout;
using std::endl;
using std::stack;
using std::string;
using std::vector;
using std::deque;
using std::queue;
using std::priority_queue;
using std::initializer_list;
using std::greater;
using std::pair;

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
class isValid_Solution 
{
public:
	bool isValid(string s);
	void demo();
};

// BM4 - 滑动窗口的最大值
class maxInWindows_Solution
{
public:
	vector<int> maxInWindows(vector<int>& num, int size);
	void demo();
};

// BM5 - 最小的K个数
class GetLeastNumbers_Solution 
{
public:
	vector<int> getLeastNumbers(vector<int>& input, int k);
	void demo();
};

// BM6 - 寻找第K大
class findKth_Solution 
{
public:
	int findKth(vector<int>& a, int n, int K);
	void demo();
};

// BM7 - 数据流的中位数
class StreamMid_Solution 
{
public:
	void Insert(int num);
	double GetMedian();

	void demo();

private:
	priority_queue<int, vector<int>> m_bigTopHeap;
	priority_queue<int, vector<int>, greater<int>> m_smallTopHeap;
};

// BM8 - 表达式求值
class ExpressionEvaluation_Solution {
public:
	int solve(string s);
	pair<int, int> getResult(const string& s, int idx);

public:
	void demo();
};