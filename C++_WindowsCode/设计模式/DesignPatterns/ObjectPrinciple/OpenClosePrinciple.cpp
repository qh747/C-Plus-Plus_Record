#include "OpenClosePrinciple.h"

void OpenClosePrincipleTestDemo()
{
	AbstractOperator* pOperator = new AddOperator();
	cout << pOperator->doOperate(10, 20) << endl;
	delete pOperator;

	pOperator = new ReduceOperator();
	cout << pOperator->doOperate(10, 20) << endl;
	delete pOperator;
}