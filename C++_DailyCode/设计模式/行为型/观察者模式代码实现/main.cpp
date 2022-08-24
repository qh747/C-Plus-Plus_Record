#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*观察者类    **/
class AbstractObserver
{
public:
	virtual ~AbstractObserver() { }

public:
	virtual void update(string data) = 0;
};

class PhoneObserver : public AbstractObserver
{
public:
	PhoneObserver() { }
	virtual ~PhoneObserver() { }

public:
	virtual void update(string data)
	{
		cout << "Phone Receive Thechnology Data: " << data << endl;
	}
};

class ComputerObserver : public AbstractObserver
{
public:
	ComputerObserver() { }
	virtual ~ComputerObserver() { }

public:
	virtual void update(string data)
	{
		cout << "Computer Receive Thechnology Data: " << data << endl;
	}
};


/*主题类    **/
class AbstractTopic
{
public:
	virtual ~AbstractTopic() { }

public:
	virtual void registerObj(AbstractObserver* observerPtr) = 0;
	virtual void unRegisterObj(AbstractObserver* observerPtr) = 0;

public:
	virtual void notifyObj(string data) = 0;
};


class TechnologyTopic : public AbstractTopic
{
public:
	TechnologyTopic() { }
	virtual ~TechnologyTopic() { }

public:
	virtual void registerObj(AbstractObserver* observerPtr)
	{
		if (m_observerArray.end() == find(m_observerArray.begin(), m_observerArray.end(), observerPtr))
		{
			m_observerArray.push_back(observerPtr);
		}
	}

	virtual void unRegisterObj(AbstractObserver* observerPtr)
	{
		vector<AbstractObserver*>::iterator iter = find(m_observerArray.begin(), m_observerArray.end(), observerPtr);
		if (m_observerArray.end() != iter)
		{
			m_observerArray.erase(iter);
		}
	}

public:
	virtual void notifyObj(string data)
	{
		for (int i = 0; i < m_observerArray.size(); ++i)
		{
			m_observerArray[i]->update(data);
		}
	}

private:
	vector<AbstractObserver*> m_observerArray;
};



int main()
{
	/*手机用户    **/
	AbstractObserver* phonePtr = new PhoneObserver();

	/*电脑用户    **/
	AbstractObserver* computerPtr = new ComputerObserver();

	/*科技类主题消息    **/
	AbstractTopic* technologyPtr = new TechnologyTopic();

	/*用户订阅消息    **/
	technologyPtr->registerObj(phonePtr);
	technologyPtr->registerObj(computerPtr);

	/*消息通知    **/
	technologyPtr->notifyObj("Good News");

	/*电脑用户取消订阅    **/
	technologyPtr->unRegisterObj(computerPtr);

	/*消息通知    **/
	technologyPtr->notifyObj("Bad News");

	delete technologyPtr;
	technologyPtr = NULL;

	delete phonePtr;
	phonePtr = NULL;

	delete computerPtr;
	computerPtr = NULL;

	system("pause");
	return 0;
}