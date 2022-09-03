#include <iostream>
#include <cstring>
using namespace std;

class Context;

/*抽象状态基类    **/
class State
{
public:
	virtual ~State() { }
	virtual void handle(const string& data, Context* pContext) = 0;
};

/*具体状态类声明    **/
class InitState : public State
{
public:
	InitState() { }
	virtual ~InitState() { }

public:
	virtual void handle(const string& data, Context* pContext);
};

class RunState : public State
{
public:
	RunState() { }
	virtual ~RunState() { }

public:
	virtual void handle(const string& data, Context* pContext);
};

class EndState : public State
{
public:
	EndState() { }
	virtual ~EndState() { }

public:
	virtual void handle(const string& data, Context* pContext);
};


/*环境类    **/
class Context
{
public:
	Context() : m_pState(new InitState())	/*默认给初始化状态    **/
	{

	}

	~Context()
	{ 
		if (NULL != m_pState)
		{
			delete m_pState;
			m_pState = NULL;
		}
	}

public:
	void HandleData(const string& data)
	{
		if (NULL != m_pState)
			m_pState->handle(data, this);

	}

	void setState(State* curState)
	{ 
		if (NULL != m_pState)
		{
			delete m_pState;
			m_pState = NULL;
		}

		m_pState = curState;
	}

private:
	State* m_pState;
};


/*具体状态类定义,单独放到环境类后定义是为了能够获取到环境类的方法    **/
void InitState::handle(const string& data, Context* pContext)
{
	cout << "Init State Receive And Record Data. Data : " << data << endl;
	pContext->setState(new RunState());		/*在状态类中可以自动切换到指定的下一个状态    **/
}

void RunState::handle(const string& data, Context* pContext)
{
	cout << "Run State Process Data. Data : " << data << endl;
	pContext->setState(new EndState());		
}

void EndState::handle(const string& data, Context* pContext)
{
	cout << "End State Destory Data. Data : " << data << endl;
}


int main()
{
	Context* pContext = new Context();
	pContext->HandleData("Build Connection");
	pContext->HandleData("Data Stream");
	pContext->HandleData("Destory Connection");

	delete pContext;
	pContext = NULL;

	system("pause");
	return 0;
}