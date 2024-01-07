#include "SequenceStack.h"

void SequenceStack::push(int val)
{
	if (m_stackContainer.size() >= m_maxSize && -1 != m_maxSize)
	{
		cerr << "The Sequence Stack Is Full." << endl;
		return;
	}
	else	
		m_stackContainer.push_back(val);
}

void SequenceStack::pop()
{
	if (m_stackContainer.size() <= 0)
	{
		cerr << "The Sequence Stack Is Empty." << endl;
		return;
	}
	else 
	{
		vector<int>::iterator iter = m_stackContainer.end();
		--iter;
		m_stackContainer.erase(iter);
	}
}

int	SequenceStack::top()
{
	if (m_stackContainer.size() <= 0)
	{
		cerr << "The Sequence Stack Is Empty." << endl;
		return -1;
	}
	else
	{
		vector<int>::iterator iter = m_stackContainer.end();
		--iter;
		return *iter;
	}
}