#include "Strategy.h"

void StrategyTestDemo()
{
	AbstractStrategy* pAdd = new AddStrategy();
	ContextClass context(pAdd);
	cout << context.doOperate(20, 10) << endl;

	AbstractStrategy* pReduce = new ReduceStrategy();
	context.setStrategy(pReduce);
	cout << context.doOperate(20, 10) << endl;

	delete pAdd;
	delete pReduce;
}