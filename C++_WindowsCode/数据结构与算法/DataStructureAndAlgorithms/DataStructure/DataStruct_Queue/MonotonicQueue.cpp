#include "MonotonicQueue.h"

void IncreaseMonotonicQueue::push(int val)
{
	while (!m_que.empty() && m_que.front() >= val) {
		m_que.pop();
	}
	m_que.push(val);
}

void IncreaseMonotonicQueue::pop()
{
	try {
		if (m_que.empty()) {
			throw "Monotonic Queue Is Empty";
		}
		else
			m_que.pop();
	}
	catch (const string& err) {
		cerr << err << endl;
	}
}

int IncreaseMonotonicQueue::top()
{
	try {
		if (m_que.empty()) {
			throw "Monotonic Queue Is Empty";
		}
		else
			return m_que.front();
	}
	catch (const string& err) {
		cerr << err << endl;
	}
}

void DecreaseMonotonicQueue::push(int val)
{
	while (!m_que.empty() && m_que.front() <= val) {
		m_que.pop();
	}
	m_que.push(val);
}

void DecreaseMonotonicQueue::pop()
{
	try {
		if (m_que.empty()) {
			throw "Monotonic Queue Is Empty";
		}
		else
			m_que.pop();
	}
	catch (const string& err) {
		cerr << err << endl;
	}
}

int DecreaseMonotonicQueue::top()
{
	try {
		if (m_que.empty()) {
			throw "Monotonic Queue Is Empty";
		}
		else
			return m_que.front();
	}
	catch (const string& err) {
		cerr << err << endl;
	}
}