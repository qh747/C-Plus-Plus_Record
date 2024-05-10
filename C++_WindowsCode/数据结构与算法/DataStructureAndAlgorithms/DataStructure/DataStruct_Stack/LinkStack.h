#pragma once
#include <iostream>
#include "../DataStruct_LinkList/SingleLinkList.h"
using namespace std;

/*Á´Ê½Õ»									**/
class LinkStack
{
public:
	LinkStack()						{ m_maxSize = -1; }
	LinkStack(int stackMaxSize)		{ m_maxSize = stackMaxSize; }
	~LinkStack()					{ }

public:
	inline int		size()			{ return m_stackContainer.size(); }
	inline bool		empty()			{ return (m_stackContainer.size() <= 0) ? true : false; }
	void			push(int val);
	void			pop();
	int				top();

private:
	SingleLinkList	m_stackContainer;
	int				m_maxSize;
};
