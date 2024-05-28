#pragma once
#include <iostream>
#include <vector>
using namespace std;

/*À≥–Ú∂”¡–									**/
class SequenceQueue
{
public:
	SequenceQueue()					{ m_maxSize = -1; }
	SequenceQueue(int stackMaxSize) { m_maxSize = stackMaxSize; }
	~SequenceQueue()				{}

public:
	inline int		size() { return m_stackContainer.size(); }
	inline bool		empty() { return m_stackContainer.empty(); }
	void			push(int val);
	void			pop();
	int				top();

private:
	vector<int>		m_stackContainer;
	int				m_maxSize;
};