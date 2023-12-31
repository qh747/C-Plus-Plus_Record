#include "LinkStack.h"

void LinkStack::push(int val)
{
	if (m_stackContainer.size() >= m_maxSize)
	{
		cerr << "The Link Stack Is Full." << endl;
		return;
	}
	else
		m_stackContainer.pushBack(val);
}

void LinkStack::pop()
{
	if (m_stackContainer.size() <= 0)
	{
		cerr << "The Link Stack Is Empty." << endl;
		return;
	}
	else
	{
		m_stackContainer.erase(m_stackContainer.size() - 1);
	}
}

int	LinkStack::top()
{
	if (m_stackContainer.size() <= 0)
	{
		cerr << "The Link Stack Is Empty." << endl;
		return -1;
	}
	else
	{
		int val = m_stackContainer.at(m_stackContainer.size() - 1);
		return val;
	}
}