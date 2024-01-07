#include "SequenceQueue.h"

void SequenceQueue::push(int val)
{
	if (m_stackContainer.size() >= m_maxSize && -1 != m_maxSize)
	{
		cerr << "The Sequence Queue Is Full." << endl;
		return;
	}
	else
		m_stackContainer.push_back(val);
}

void SequenceQueue::pop()
{
	if (m_stackContainer.size() <= 0)
	{
		cerr << "The Sequence Queue Is Empty." << endl;
		return;
	}
	else
	{
		m_stackContainer.erase(m_stackContainer.begin());
	}
}

int	SequenceQueue::top()
{
	if (m_stackContainer.size() <= 0)
	{
		cerr << "The Sequence Queue Is Empty." << endl;
		return -1;
	}
	else
	{
		vector<int>::iterator iter = m_stackContainer.begin();
		return *iter;
	}
}