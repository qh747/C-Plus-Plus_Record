#include "DynamicArrayAdv.h"

DynamicArrayAdv::DynamicArrayAdv()
{
	this->initArray();
}

DynamicArrayAdv::~DynamicArrayAdv()
{
	if (m_pArray != m_arrayBuffer)
		delete[] m_pArray;
}

void DynamicArrayAdv::pushBack(int val)
{
	this->extendArray(m_arraySize + 1);
	m_pArray[m_arraySize] = val;
	++m_arraySize;
}

void DynamicArrayAdv::insert(size_t pos, int val)
{
	if(pos > m_arraySize)
		return;
	
	this->extendArray(m_arraySize + 1);
	this->moveBack(pos);
	m_pArray[pos] = val;
	++m_arraySize;
}

void DynamicArrayAdv::erase(size_t pos)
{
	if (pos >= m_arraySize)
		return;

	this->moveForward(pos);
	--m_arraySize;
}

void DynamicArrayAdv::clear()
{
	if (m_pArray != m_arrayBuffer)
		delete[] m_pArray;

	this->initArray();
}

int& DynamicArrayAdv::operator[](size_t pos)
{
	return m_pArray[pos];
}

const int& DynamicArrayAdv::operator[](size_t pos) const
{
	return this->operator[](pos);
}

int& DynamicArrayAdv::at(size_t pos)
{
	if (pos >= m_arraySize)
		throw "POSITION INVALID";
	else
		return this->operator[](pos);
}

const int& DynamicArrayAdv::at(size_t pos) const
{
	return this->at(pos);
}

void DynamicArrayAdv::initArray()
{
	m_arraySize = 0;
	m_arrayCapacity = sizeof(m_arrayBuffer) / sizeof(m_arrayBuffer[0]);
	memset(m_arrayBuffer, 0, sizeof(m_arrayBuffer));
	m_pArray = m_arrayBuffer;
}

void DynamicArrayAdv::extendArray(size_t size)
{
	if (size < m_arrayCapacity)
		return;

	m_arrayCapacity = size * 2;
	int* pNewArray = new int[m_arrayCapacity];

	if (m_pArray == m_arrayBuffer)
	{
		memcpy(pNewArray, m_arrayBuffer, sizeof(int) * m_arraySize);
		m_pArray = pNewArray;
	}
	else
	{
		memcpy(pNewArray, m_pArray, sizeof(int) * m_arraySize);
		
		delete[] m_pArray;
		m_pArray = pNewArray;
	}
}

void DynamicArrayAdv::moveBack(size_t pos)
{
	for (int index = m_arraySize - 1; index >= pos; --index)
	{
		if (index < 0)
			break;
		else
			m_pArray[index + 1] = m_pArray[index];
	}
}

void DynamicArrayAdv::moveForward(size_t pos)
{
	for (int index = pos; index <= m_arraySize - 1; ++index)
	{
		m_pArray[index] = m_pArray[index + 1];
	}
}
