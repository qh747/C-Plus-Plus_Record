#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// 抽象资源类
class AbstractElement
{
public:
	virtual ~AbstractElement() {}

public:
	virtual void showInfo() = 0;
};

// 具体资源类一
class SpecficElementFst : public AbstractElement
{
public:
	SpecficElementFst() : AbstractElement() {}
	virtual ~SpecficElementFst() {}

public:
	virtual void showInfo() { cout << "First Specific Info" << endl; }
};

// 具体资源类二
class SpecficElementSec : public AbstractElement
{
public:
	SpecficElementSec() : AbstractElement() {}
	virtual ~SpecficElementSec() {}

public:
	virtual void showInfo() { cout << "Second Specific Info" << endl; }
};

// 新抽象资源类
class NewAbstractElement
{
public:
	virtual ~NewAbstractElement() {}

public:
	virtual void showNewInfo() = 0;
};

// 新具体资源类一
class NewSpecficElementFst : public NewAbstractElement
{
public:
	NewSpecficElementFst() : NewAbstractElement() {}
	virtual ~NewSpecficElementFst() {}

public:
	virtual void showNewInfo() { cout << "First New Specific Info" << endl; }
};

// 新具体资源类二
class NewSpecficElementSec : public NewAbstractElement
{
public:
	NewSpecficElementSec() : NewAbstractElement() {}
	virtual ~NewSpecficElementSec() {}

public:
	virtual void showNewInfo() { cout << "Second New Specific Info" << endl; }
};