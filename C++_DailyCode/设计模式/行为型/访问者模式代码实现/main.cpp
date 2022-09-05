#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vistor;

/*元素类声明    **/
class AbstractElement
{
public:
	AbstractElement(const string& eleNameStr) : m_elementName(eleNameStr) { }
	virtual ~AbstractElement() { }

public:
	virtual void accept(Vistor* pVistor) = 0;

public:
	string getName() { return m_elementName; }

protected:
	string m_elementName;
};

class CPUElement : public AbstractElement
{
public:
	CPUElement(const string& eleNameStr) : AbstractElement(eleNameStr) { }
	virtual ~CPUElement() { }

public:
	virtual void accept(Vistor* pVistor);
};

class Screenlement : public AbstractElement
{
public:
	Screenlement(const string& eleNameStr) : AbstractElement(eleNameStr) { }
	virtual ~Screenlement() { }

public:
	virtual void accept(Vistor* pVistor);
};

class MainBoardlement : public AbstractElement
{
public:
	MainBoardlement(const string& eleNameStr) : AbstractElement(eleNameStr) { }
	virtual ~MainBoardlement() { }

public:
	virtual void accept(Vistor* pVistor);
};

/*访问者类    **/
class Vistor
{
public:
	virtual ~Vistor() { }

public:
	virtual void visitCPU(AbstractElement* pCPU) = 0;
	virtual void visitScreen(AbstractElement* pScreen) = 0;
	virtual void visitMainBoard(AbstractElement* pMainBoard) = 0;
};

class SimpleChecker : public Vistor
{
public:
	SimpleChecker() { }
	virtual ~SimpleChecker() { }

public:
	virtual void visitCPU(AbstractElement* pCPU)
	{
		cout << "Simple Checker Check Element: " << pCPU->getName() << " Is Normal." << endl;
	}

	virtual void visitScreen(AbstractElement* pScreen)
	{
		cout << "Simple Checker Check Element: " << pScreen->getName() << " Is Normal." << endl;
	}

	virtual void visitMainBoard(AbstractElement* pMainBoard)
	{
		cout << "Simple Checker Check Element: " << pMainBoard->getName() << " Is Normal." << endl;
	}
};

class MiddleChecker : public Vistor
{
public:
	MiddleChecker() { }
	virtual ~MiddleChecker() { }

public:
	virtual void visitCPU(AbstractElement* pCPU)
	{
		cout << "Middle Checker Check Element: " << pCPU->getName() << " Is Wrong. But Can't Fixed." << endl;
	}

	virtual void visitScreen(AbstractElement* pScreen)
	{
		cout << "Middle Checker Check Element: " << pScreen->getName() << " Is Normal." << endl;
	}

	virtual void visitMainBoard(AbstractElement* pMainBoard)
	{
		cout << "Middle Checker Check Element: " << pMainBoard->getName() << " Is Normal." << endl;
	}
};

class HighChecker : public Vistor
{
public:
	HighChecker() { }
	virtual ~HighChecker() { }

public:
	virtual void visitCPU(AbstractElement* pCPU)
	{
		cout << "High Checker Check Element: " << pCPU->getName() << " Is Wrong. It's Easy To Fix." << endl;
	}

	virtual void visitScreen(AbstractElement* pScreen)
	{
		cout << "High Checker Check Element: " << pScreen->getName() << " Is Wrong. It's Easy To Fix." << endl;
	}

	virtual void visitMainBoard(AbstractElement* pMainBoard)
	{
		cout << "High Checker Check Element: " << pMainBoard->getName() << " Is Wrong. It's Easy To Fix." << endl;
	}
};

/*元素类定义    **/
void CPUElement::accept(Vistor* pVistor)
{
	pVistor->visitCPU(this);
}

void Screenlement::accept(Vistor* pVistor)
{
	pVistor->visitScreen(this);
}

void MainBoardlement::accept(Vistor* pVistor)
{
	pVistor->visitMainBoard(this);
}

/*元素组合类    **/
class Computer
{
public:
	Computer() { }
	~Computer() { }

public:
	void addEleent(AbstractElement* pElement)
	{
		m_elementArray.push_back(pElement);
	}

	void accept(Vistor* pVistor)
	{
		for (int i = 0; i < m_elementArray.size(); ++i)
		{
			m_elementArray[i]->accept(pVistor);
		}
	}

private:
	vector<AbstractElement*> m_elementArray;
};

int main()
{
	/*元素创建    **/
	AbstractElement* pCPU = new CPUElement(string("CPU"));
	AbstractElement* pScreen = new Screenlement(string("SCREEN"));
	AbstractElement* pMainBoard = new MainBoardlement(string("MAIN BOARD"));

	/*组合类创建    **/
	Computer* pComputer = new Computer();
	pComputer->addEleent(pCPU);
	pComputer->addEleent(pScreen);
	pComputer->addEleent(pMainBoard);

	/*访问者类创建    **/
	Vistor* pSimpleChecker = new SimpleChecker();
	Vistor* pMiddleChecker = new MiddleChecker();
	Vistor* pHighChecker = new HighChecker();

	/*访问者访问元素    **/
	pComputer->accept(pSimpleChecker);
	pComputer->accept(pMiddleChecker);
	pComputer->accept(pHighChecker);

	/*内存释放    **/
	delete pCPU;
	pCPU = NULL;

	delete pScreen;
	pScreen = NULL;

	delete pMainBoard;
	pMainBoard = NULL;

	delete pComputer;
	pComputer = NULL;

	delete pSimpleChecker;
	pSimpleChecker = NULL;

	delete pMiddleChecker;
	pMiddleChecker = NULL;

	delete pHighChecker;
	pHighChecker = NULL;

	system("pause");
	return 0;
}