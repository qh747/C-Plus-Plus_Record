#pragma once
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using std::cout;
using std::endl;
using std::list;
using std::string;

// 组合模式
class AbstractComponent
{
public:
	AbstractComponent(const string& name) : m_name(name) {}
	virtual ~AbstractComponent() {}
	virtual void				addChild(AbstractComponent* componentPtr) = 0;
	virtual bool				removeChild(const string& name) = 0;
	virtual void				showName() = 0;
	virtual AbstractComponent*	getChild(const string& name) = 0;
	const   string&             getName() { return m_name; }

protected:
	string m_name;
};

class BranchComponent : public AbstractComponent
{
public:
	BranchComponent(const string& name) : AbstractComponent(name) {}
	virtual ~BranchComponent() {}
	virtual void addChild(AbstractComponent* componentPtr);
	virtual bool removeChild(const string& name);
	virtual void showName();
	virtual AbstractComponent* getChild(const string& name);

protected:
	list<AbstractComponent*> m_componentList;
};

class LeafComponent : public AbstractComponent
{
public:
	LeafComponent(const string& name) : AbstractComponent(name) {}
	virtual ~LeafComponent() {}
	virtual void addChild(AbstractComponent* componentPtr) { return; }
	virtual bool removeChild(const string& name) { return false; }
	virtual void showName() { cout << " -File: " << getName() << endl; }
	virtual AbstractComponent* getChild(const string& name) { return NULL; }
};

// 组合模式测试函数
void ComponentModeTestDemo();