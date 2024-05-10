#include "DynamicArray.h"

DynamicArray::DynamicArray() : m_capacity(0), m_size(0), m_pArray(NULL)
{
	this->initArray();
}

DynamicArray::DynamicArray(unsigned int capacity) : m_capacity(0), m_size(0), m_pArray(NULL)
{
	if (0 == capacity)
		this->initArray();
	else
		this->initArray(capacity);
}

DynamicArray::~DynamicArray()
{
	if (NULL != m_pArray)
		delete[] m_pArray;
}

void DynamicArray::addVal(int val)
{
	if (m_size + 1 >= m_capacity)
		this->extendArray(m_size + 1);

	m_pArray[m_size] = val;
	++m_size;
}

void DynamicArray::insertVal(unsigned int pos, int val)
{
	if (m_size + 1 >= m_capacity)
		this->extendArray(m_size + 1);

	for (int i = (m_size - 1); i >= pos; --i)
	{
		if (0 > i)
			break;
		else
			m_pArray[i + 1] = m_pArray[i];
	}

	m_pArray[pos] = val;
	++m_size;
}

void DynamicArray::modifyVal(unsigned int pos, int val)
{
	if (pos < 0 || pos >= m_size)
		return;

	m_pArray[pos] = val;
}

int DynamicArray::getVal(unsigned int pos)
{
	if (pos < 0 || pos >= m_size)
		return -1;

	return m_pArray[pos];
}

void DynamicArray::delVal(unsigned int pos)
{
	if (pos < 0 || pos >= m_size)
		return;

	for (int i = pos; i < (m_size - 1); ++i)
	{
		m_pArray[i] = m_pArray[i + 1];
	}

	--m_size;
}

void DynamicArray::clear()
{
	for (int i = 0; i < m_size; ++i)
	{
		m_pArray[i] = -1;
	}

	m_size = 0;
}

unsigned int DynamicArray::getSize()
{
	return m_size;
}

unsigned int DynamicArray::getCapacity()
{
	return m_capacity;
}

void DynamicArray::initArray(unsigned int capacity)
{
	m_size = 0;
	m_capacity = capacity;
	m_pArray = new int[m_capacity];
}

bool DynamicArray::extendArray(unsigned int capacity)
{
	/*容量拓展												**/
	if (capacity <= m_capacity)
		return false;                                       // 不需要拓展
	else if ((capacity * 2) >= m_capacity)					
		m_capacity *= 2;									// 现有容量2倍拓展
	else                                           
		m_capacity = capacity * 2;							// 参数容量2倍拓展

	/*数据拓拷贝											**/
	int* pNewArray = new int[m_capacity];
	for (int i = 0; i < m_size; ++i)
	{
		pNewArray[i] = m_pArray[i];
	}

	/*数据地址变更											**/
	if (NULL != m_pArray)
		delete[] m_pArray;
	m_pArray = pNewArray;

	return true;
}