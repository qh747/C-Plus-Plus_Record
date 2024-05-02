#include "Interpreter.h"

void Client::expressProcess()
{
	if (NULL != m_pExpress)
		clearCache();

	stack<AbstractExpression*> expressStack;

	// 解释器构建
	string contextStr = m_pContext->getText();
	for (int i = 0; i < contextStr.size(); ++i)
	{
		if ('+' == contextStr[i])
		{
			AbstractExpression* pLeft = expressStack.top();
			expressStack.pop();
			expressStack.push(new AddExpresion(pLeft, new TerminalExpression(contextStr[++i])));
			
		}
		else if ('-' == contextStr[i])
		{
			AbstractExpression* pLeft = expressStack.top();
			expressStack.pop();
			expressStack.push(new ReduceExpresion(pLeft, new TerminalExpression(contextStr[++i])));
		}
		else
			expressStack.push(new TerminalExpression(contextStr[i]));
	}

	// 解释器暂存
	m_pExpress = expressStack.top();
	expressStack.pop();

	// 解释器结果获取
	m_Result = m_pExpress->interpret(m_expressMap);
}

void Client::releaseExpressionNode(AbstractExpression* pCurrentNode)
{
	if (NULL == pCurrentNode)
		return;

	TerminalExpression* pTerminalNode = dynamic_cast<TerminalExpression *>(pCurrentNode);
	if (NULL != pTerminalNode)
	{
		delete pTerminalNode;
		return;
	}

	NonTerminalExpression* pNonTerminalNode = dynamic_cast<NonTerminalExpression*>(pCurrentNode);
	if (NULL != pNonTerminalNode)
	{
		releaseExpressionNode(pNonTerminalNode->getLeft());
		releaseExpressionNode(pNonTerminalNode->getRight());
		delete pNonTerminalNode;
	}
}

void InterpreterTestDemo()
{
	Interpreter::Context context("a+b-c+d-e");

	map<char, int> expresssMap;
	expresssMap.insert(std::make_pair('a', 1));
	expresssMap.insert(std::make_pair('b', 2));
	expresssMap.insert(std::make_pair('c', 3));
	expresssMap.insert(std::make_pair('d', 4));
	expresssMap.insert(std::make_pair('e', 5));

	Client client;
	client.setContext(&context);
	client.setExpressMap(expresssMap);

	client.expressProcess();
	cout << context.getText() << "=" << client.getResult() << endl;
}