#include "SimpleFactory.h"

AbstractElement* SimpleFactory::createElement(const string& name)
{
	if ("SpecficElementFst" == name)
		return new SpecficElementFst();
	else if ("SpecficElementSec" == name)
		return new SpecficElementSec();
	else
		return nullptr;
}

void SimpleFactoryTestDemo()
{
	AbstractElement* pFstElement = SimpleFactory::createElement("SpecficElementFst");
	pFstElement->showInfo();
	delete pFstElement;

	AbstractElement* pSecElement = SimpleFactory::createElement("SpecficElementSec");
	pSecElement->showInfo();
	delete pSecElement;
}