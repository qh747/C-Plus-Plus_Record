#pragma once
#include <iostream>
#include <vector>
using namespace std;

/*À≥–Ú’ª									**/
class SequenceStack
{
public:
	SequenceStack()							{ m_maxSize = -1; }
	SequenceStack(int stackMaxSize)			{ m_maxSize = stackMaxSize; }
	~SequenceStack()						{ }

public:
	inline int		size()					{ return m_stackContainer.size(); }
	inline bool		empty()					{ return m_stackContainer.empty(); }
	void			push(int val);
	void			pop();
	int				top();

private:
	vector<int>		m_stackContainer;
	int				m_maxSize;
};
