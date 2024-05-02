#include "AbstractFactory.h"

AbstractElement* FirstFactory::createElement()
{
	return new SpecficElementFst();
}

NewAbstractElement* FirstFactory::createNewElement()
{
	return new NewSpecficElementFst();
}

AbstractElement* SecondFactory::createElement()
{
	return new SpecficElementSec();
}

NewAbstractElement* SecondFactory::createNewElement()
{
	return new NewSpecficElementSec();
}

void AbstractFactoryTestDemo()
{
	AbstractFactory* pFactory = new FirstFactory();
	AbstractElement* pElem = pFactory->createElement();
	pElem->showInfo();
	NewAbstractElement* pNewElem = pFactory->createNewElement();
	pNewElem->showNewInfo();

	delete pFactory;
	delete pElem;
	delete pNewElem;

	pFactory = new SecondFactory();
	pElem = pFactory->createElement();
	pElem->showInfo();
	pNewElem = pFactory->createNewElement();
	pNewElem->showNewInfo();

	delete pFactory;
	delete pElem;
	delete pNewElem;
}