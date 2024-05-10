#pragma once
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::string;

class Vistor;

// 元素类
class AbstractElem
{
public:
	AbstractElem(const string& name, const string& id) : m_eleName(name), m_eleId(id){}
	virtual ~AbstractElem() {}
	virtual void accept(Vistor* pVistor) = 0;

protected:
	string m_eleName;
	string m_eleId;
};

// 访问者类
class Vistor
{
public:
	virtual ~Vistor() {}
	virtual void visitCPU(AbstractElem* ele) = 0;
	virtual void visitScreen(AbstractElem* ele) = 0;
	virtual void visitMainBoard(AbstractElem* ele) = 0;
};

class CPUElem : public AbstractElem
{
public:
	CPUElem(const string& name, const string& id) : AbstractElem(name, id) {}
	virtual ~CPUElem() {}
	virtual void accept(Vistor* vistor) { vistor->visitCPU(this); }
	virtual const string& getCpuName() { return m_eleName; }
	virtual const string& getCpuId() { return m_eleId; }
};

class ScreenElem : public AbstractElem
{
public:
	ScreenElem(const string& name, const string& id) : AbstractElem(name, id) {}
	virtual ~ScreenElem() {}
	virtual void accept(Vistor* pVistor) { pVistor->visitScreen(this); }
	virtual const string& getScreenName() { return m_eleName; }
	virtual const string& getScreenId() { return m_eleId; }
};

class MainBoardElem : public AbstractElem
{
public:
	MainBoardElem(const string& name, const string& id) : AbstractElem(name, id) {}
	virtual ~MainBoardElem() {}
	virtual void accept(Vistor* pVistor) { pVistor->visitMainBoard(this); }
	virtual const string& getMainBoardName() { return m_eleName; }
	virtual const string& getMainBoardId() { return m_eleId; }
};

class SimpleChecker : public Vistor
{
public:
	virtual ~SimpleChecker() {}

	virtual void visitCPU(AbstractElem* ele)
	{
		CPUElem* cpu = dynamic_cast<CPUElem*>(ele);
		cout << "Simple Check Element: " << cpu->getCpuName() << endl;
	}

	virtual void visitScreen(AbstractElem* ele)
	{
		ScreenElem* scren = dynamic_cast<ScreenElem*>(ele);
		cout << "Simple Check Element: " << scren->getScreenName() << endl;
	}

	virtual void visitMainBoard(AbstractElem* ele)
	{
		MainBoardElem* mainBoard = dynamic_cast<MainBoardElem*>(ele);
		cout << "Simple Check Element: " << mainBoard->getMainBoardName() << endl;
	}
};

class HighChecker : public Vistor
{
public:
	virtual ~HighChecker() {}

	virtual void visitCPU(AbstractElem* ele)
	{
		CPUElem* cpu = dynamic_cast<CPUElem*>(ele);
		cout << "High Check Element: " << cpu->getCpuName() << " " << cpu->getCpuId() << endl;
	}

	virtual void visitScreen(AbstractElem* ele)
	{
		ScreenElem* scren = dynamic_cast<ScreenElem*>(ele);
		cout << "High Check Element: " << scren->getScreenName() << " " << scren->getScreenId() << endl;
	}

	virtual void visitMainBoard(AbstractElem* ele)
	{
		MainBoardElem* mainBoard = dynamic_cast<MainBoardElem*>(ele);
		cout << "High Check Element: " << mainBoard->getMainBoardName() << " " << mainBoard->getMainBoardId() << endl;
	}
};

// 元素组合类
class Computer
{
public:
	Computer() 
	{ 
		m_elementArray.push_back(new CPUElem("cpu", "1"));
		m_elementArray.push_back(new ScreenElem("screen", "2"));
		m_elementArray.push_back(new MainBoardElem("mainboard", "3"));
	}

	~Computer() 
	{ 
		while (!m_elementArray.empty())
		{
			delete (*m_elementArray.begin());
			m_elementArray.erase(m_elementArray.begin());
		}
	}

	void accept(Vistor* vistor)
	{
		for (int i = 0; i < m_elementArray.size(); ++i)
		{
			m_elementArray[i]->accept(vistor);
		}
	}

private:
	vector<AbstractElem*> m_elementArray;
};

// 访问者模式测试函数
void VistorTestDemo();