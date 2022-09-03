#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <stack>
using namespace std;

/*文本类    **/
class Context
{
public:
	Context() { }
	~Context() { }

public:
	void setText(string text)
	{
		m_text = text;
	}

	string getText()
	{
		return m_text;
	}

private:
	string m_text;
};

/*抽象解析器类    **/
class AbstractExpression
{
public:
	virtual ~AbstractExpression() { }

public:
	virtual int interpret(const map<char, int>& dataMap) = 0;
};

/*终端解释器类    **/
class TerminalExpression :public AbstractExpression
{
public:
	TerminalExpression(char numberStr) : m_numberStr(numberStr)	{ }
	virtual ~TerminalExpression() { }

public:
	virtual int interpret(const map<char, int>& dataMap)
	{
		return dataMap.at(m_numberStr);
	}

private:
	char m_numberStr;
};

/*非终端解释器基类    **/
class NonTerminalExpression : public AbstractExpression
{
public:
	NonTerminalExpression(AbstractExpression* pLeft, AbstractExpression* pRight) : m_leftNode(pLeft), m_rightNode(pRight) { }
	virtual ~NonTerminalExpression() { }

public:
	AbstractExpression* getLeftNode() { return m_leftNode; }
	void setLeftNode(AbstractExpression* pLeftNode) { m_leftNode = pLeftNode; }

	AbstractExpression* getRightNode() { return m_rightNode; }
	void setRightNode(AbstractExpression* pRightNode) { m_rightNode = pRightNode; }

public:
	virtual int interpret(const map<char, int>& dataMap) = 0;

protected:
	AbstractExpression* m_leftNode;
	AbstractExpression* m_rightNode;
};

/*加法解释器类    **/
class AddExpresion : public NonTerminalExpression
{
public:
	AddExpresion(AbstractExpression* pLeft, AbstractExpression* pRight) : NonTerminalExpression(pLeft, pRight) { }
	virtual ~AddExpresion() { }

public:
	virtual int interpret(const map<char, int>& dataMap)
	{
		return m_leftNode->interpret(dataMap) + m_rightNode->interpret(dataMap);
	}
};

/*减法解释器类    **/
class ReduceExpresion : public NonTerminalExpression
{
public:
	ReduceExpresion(AbstractExpression* pLeft, AbstractExpression* pRight) : NonTerminalExpression(pLeft, pRight) { }
	virtual ~ReduceExpresion() { }

public:
	virtual int interpret(const map<char, int>& dataMap)
	{
		return m_leftNode->interpret(dataMap) - m_rightNode->interpret(dataMap);
	}
};

/*客户类    **/
class Client
{
public:
	Client() : m_pContext(NULL), m_pExpress(NULL), m_Result(0) { }
	~Client() { clearCache(); }

public:
	void setContext(Context* pContext)
	{
		m_pContext = pContext;
	}

	void setExpressMap(const map<char, int>& expressMap)
	{
		m_expressMap = expressMap;
	}

	void expressProcess()
	{
		if (NULL != m_pExpress)
			clearCache();

		/*解释器构建     **/
		string contextStr = m_pContext->getText();

		stack<AbstractExpression*> expressStack;
		AbstractExpression* pLeftExpressNode = NULL;
		AbstractExpression* pRightExpressNode = NULL;

		for (int i = 0; i < contextStr.size(); ++i)
		{
			if ('+' == contextStr[i])
			{
				/*非终端解释器类创建    **/
				pLeftExpressNode = expressStack.top();
				expressStack.pop();

				pRightExpressNode = new TerminalExpression(contextStr[++i]);
				expressStack.push(new AddExpresion(pLeftExpressNode, pRightExpressNode));
			}
			else if ('-' == contextStr[i])
			{
				/*非终端解释器类创建    **/
				pLeftExpressNode = expressStack.top();
				expressStack.pop();

				pRightExpressNode = new TerminalExpression(contextStr[++i]);
				expressStack.push(new ReduceExpresion(pLeftExpressNode, pRightExpressNode));
			}
			else
			{
				/*终端解释器类创建    **/
				expressStack.push(new TerminalExpression(contextStr[i]));
			}
		}

		/*解释器内容获取    **/
		m_pExpress = expressStack.top();
		expressStack.pop();

		m_Result = m_pExpress->interpret(m_expressMap);
	}

	int getResult()
	{
		return m_Result;
	}

private:
	void clearCache()
	{
		releaseExpressionNode(m_pExpress);
	}

	void releaseExpressionNode(AbstractExpression* pCurrentNode)
	{
		if (NULL == pCurrentNode)
			return;

		TerminalExpression* pTerminalNode = dynamic_cast<TerminalExpression *>(pCurrentNode);
		if (NULL != pTerminalNode)
		{
			delete pTerminalNode;
			pTerminalNode = NULL;

			return;
		}

		NonTerminalExpression* pNonTerminalNode = dynamic_cast<NonTerminalExpression*>(pCurrentNode);
		if (NULL != pNonTerminalNode)
		{
			releaseExpressionNode(pNonTerminalNode->getLeftNode());
			pNonTerminalNode->setLeftNode(NULL);

			releaseExpressionNode(pNonTerminalNode->getRightNode());
			pNonTerminalNode->setRightNode(NULL);

			delete pNonTerminalNode;
			pNonTerminalNode = NULL;
		}
	}

private:
	map<char, int>              m_expressMap;
	Context*					m_pContext;
	AbstractExpression*			m_pExpress;
	int							m_Result;
};

int main()
{
	Context* pContext = new Context();
	pContext->setText(string("a+b-c+d-e"));

	Client* pCLient = new Client();
	pCLient->setContext(pContext);

	map<char, int> expresssMap;
	expresssMap.insert(make_pair('a', 1));
	expresssMap.insert(make_pair('b', 2));
	expresssMap.insert(make_pair('c', 3));
	expresssMap.insert(make_pair('d', 4));
	expresssMap.insert(make_pair('e', 5));
	pCLient->setExpressMap(expresssMap);

	pCLient->expressProcess();

	int result = pCLient->getResult();
	cout << pContext->getText() << " = " << result << endl;

	delete pCLient;
	pCLient = NULL;

	delete pContext;
	pContext = NULL;

	system("pause");
}