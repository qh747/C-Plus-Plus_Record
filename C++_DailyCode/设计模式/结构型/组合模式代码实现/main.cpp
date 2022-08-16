#include <iostream>
#include <list>
#include <cstring>
#include <string>
using namespace std;

/*抽象基类, 说明树叶节点和树枝节点使用的方法    **/
class AbstractComponent
{
public:
	AbstractComponent(const string& name) : m_name(name)
	{

	}

	virtual ~AbstractComponent()
	{

	}

public:
	virtual void				addChild(AbstractComponent* componentPtr) = 0;
	virtual bool				removeChild(const string& name) = 0;
	virtual void				showName() = 0;
	virtual AbstractComponent*	getChild(const string& name) = 0;
	const string&               getName() { return m_name; }

protected:
	string m_name;
};

/*树枝节点类, 可以添加树叶节点    **/
class BranchComposite : public AbstractComponent
{
public:
	BranchComposite(const string& name) : AbstractComponent(name)
	{

	}

	virtual ~BranchComposite()
	{

	}

public:
	virtual void addChild(AbstractComponent* componentPtr)
	{
		m_componentList.push_back(componentPtr);
	}

	virtual bool removeChild(const string& name)
	{
		list<AbstractComponent*>::iterator eraseIter = m_componentList.end();

		list<AbstractComponent*>::iterator iter = m_componentList.begin();
		for (; iter != m_componentList.end(); iter++)
		{
			if (name == (*iter)->getName())
			{
				eraseIter = iter;
				break;
			}
		}

		if (m_componentList.end() == eraseIter)
		{
			for (iter = m_componentList.begin(); iter != m_componentList.end(); iter++)
			{
				bool eraseResult = (*iter)->removeChild(name);
				if (true == eraseResult)
					return eraseResult;
			}
		}
		else
		{
			m_componentList.erase(eraseIter);
			return true;
		}
	}

	virtual void showName()
	{
		cout << "+Dict: " << getName() << endl;
		for (list<AbstractComponent*>::iterator iter = m_componentList.begin(); iter != m_componentList.end(); iter++)
		{
			(*iter)->showName();
		}
	}

	virtual AbstractComponent* getChild(const string& name)
	{
		list<AbstractComponent*>::iterator findIter = m_componentList.end();

		list<AbstractComponent*>::iterator iter = m_componentList.begin();
		for (; iter != m_componentList.end(); iter++)
		{
			if (name == (*iter)->getName())
			{
				findIter = iter;
				break;
			}
		}

		if (m_componentList.end() == findIter)
		{
			for (iter = m_componentList.begin(); iter != m_componentList.end(); iter++)
			{
				AbstractComponent * findPtr = (*iter)->getChild(name);
				if (NULL != findPtr)
					return findPtr;
			}
		}
		else
		{
			return *findIter;
		}
	}

protected:
	list<AbstractComponent*> m_componentList;
};

/*树叶节点类, 最底层节点    **/
class LeafNode : public AbstractComponent
{
public:
	LeafNode(const string& name) : AbstractComponent(name)
	{

	}

	virtual ~LeafNode()
	{

	}

public:
	virtual void addChild(AbstractComponent* componentPtr)
	{
		return;
	}

	virtual bool removeChild(const string& name)
	{
		return false;
	}

	virtual void showName()
	{
		cout << "-File: " << getName() << endl;
	}

	virtual AbstractComponent* getChild(const string& name)
	{
		return NULL;
	}
};

int main()
{
	/*根节点目录层    **/
	AbstractComponent* rootNode = new BranchComposite(string("Root"));

	/*一级目录层    **/
	AbstractComponent* firstLevelFirstNode = new BranchComposite(string("Level 1 Dict First"));
	AbstractComponent* firstLevelSecondNode = new BranchComposite(string("Level 1 Dict Second"));
	AbstractComponent* firstLevelThirdNode = new LeafNode(string("Level 1 File First"));

	/*二级目录层    **/
	AbstractComponent* secondLevelFirstNode = new BranchComposite(string("Level 2 Dict Third"));
	AbstractComponent* scondLevelSecondNode = new LeafNode(string("Level 2 File Second"));
	AbstractComponent* secondLevelThirdNode = new BranchComposite(string("Level 2 Dict Forth"));

	/*三级目录层    **/
	AbstractComponent* thirdLevelFirstNode = new LeafNode(string("Level 3 File Third"));
	AbstractComponent* thirdLevelSecondNode = new LeafNode(string("Level 3 File Forth"));
	AbstractComponent* thirdLevelThirdNode = new LeafNode(string("Level 3 File Fifth"));
	AbstractComponent* thirdLevelForthNode = new LeafNode(string("Level 3 File Sixth"));
	AbstractComponent* thirdLevelFifthNode = new LeafNode(string("Level 3 File Seventh"));

	/*目录搭建    **/
	rootNode->addChild(firstLevelFirstNode);
	rootNode->addChild(firstLevelSecondNode);
	rootNode->addChild(firstLevelThirdNode);

	firstLevelFirstNode->addChild(secondLevelFirstNode);
	firstLevelFirstNode->addChild(scondLevelSecondNode);

	firstLevelSecondNode->addChild(secondLevelThirdNode);

	secondLevelFirstNode->addChild(thirdLevelFirstNode);

	secondLevelThirdNode->addChild(thirdLevelSecondNode);
	secondLevelThirdNode->addChild(thirdLevelThirdNode);
	secondLevelThirdNode->addChild(thirdLevelForthNode);
	secondLevelThirdNode->addChild(thirdLevelFifthNode);

	/*目录层级显示    **/
	rootNode->showName();


	delete rootNode;

	delete firstLevelFirstNode;
	delete firstLevelSecondNode;
	delete firstLevelThirdNode;

	delete secondLevelFirstNode;
	delete scondLevelSecondNode;
	delete secondLevelThirdNode;

	delete thirdLevelFirstNode;
	delete thirdLevelSecondNode;
	delete thirdLevelThirdNode;
	delete thirdLevelForthNode;
	delete thirdLevelFifthNode;

	rootNode = NULL;

	firstLevelFirstNode	   = NULL;
	firstLevelSecondNode   = NULL;
	firstLevelThirdNode	   = NULL;

	secondLevelFirstNode  = NULL;
	scondLevelSecondNode  = NULL;
	secondLevelThirdNode  = NULL;

	thirdLevelFirstNode    = NULL;
	thirdLevelSecondNode   = NULL;
	thirdLevelThirdNode	   = NULL;
	thirdLevelForthNode	   = NULL;
	thirdLevelFifthNode	   = NULL;

	system("pause");
	return 0;
}