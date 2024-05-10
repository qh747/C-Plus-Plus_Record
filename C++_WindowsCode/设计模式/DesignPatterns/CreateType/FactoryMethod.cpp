#include "FactoryMethod.h"

AbstractElement* FristFactoryMethod::createElement()
{
	return new SpecficElementFst();
}

AbstractElement* SecondFactoryMethod::createElement()
{
	return new SpecficElementSec();
}

void FactoryMethodTestDemo()
{
	FristFactoryMethod fstFactory;
	AbstractElement* pFstElement = fstFactory.createElement();
	pFstElement->showInfo();

	SecondFactoryMethod secFactory;
	AbstractElement* pSecElement = secFactory.createElement();
	pSecElement->showInfo();

	delete pFstElement;
	delete pSecElement;
}