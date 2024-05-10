#include "Mediator.h"

void FuncCollegue::sendMsg(string msg)
{
	if (nullptr != m_pMediator)
		m_pMediator->relayMsg(msg);
}

void FuncCollegue::recvMsg(string msg)
{
	cout << "Func Recv: " << msg << endl;
}

void DisplayCollegue::sendMsg(string msg)
{
	if (nullptr != m_pMediator)
		m_pMediator->relayMsg(msg);
}

void DisplayCollegue::recvMsg(string msg)
{
	cout << "Display Recv: " << msg << endl;
}

void FuncMediator::addColl(AbstractColleague* coll)
{
	m_collVec.push_back(coll);
}

void FuncMediator::relayMsg(string msg)
{
	for (vector<AbstractColleague*>::iterator iter = m_collVec.begin(); iter != m_collVec.end(); iter++)
	{
		(*iter)->recvMsg(msg);
	}
}

void DisplayMediator::addColl(AbstractColleague* coll)
{
	m_collVec.push_back(coll);
}

void DisplayMediator::relayMsg(string msg)
{
	for (vector<AbstractColleague*>::iterator iter = m_collVec.begin(); iter != m_collVec.end(); iter++)
	{
		(*iter)->recvMsg(msg);
	}
}

void MediatorTestDemo()
{
	AbstractColleague* pFuncColl = new FuncCollegue();
	AbstractColleague* pDispColl = new DisplayCollegue();

	AbstractMediator* pFuncMed = new FuncMediator();
	AbstractMediator* pDispMed = new DisplayMediator();

	pFuncColl->setMediator(pFuncMed);
	pDispColl->setMediator(pDispMed);

	pFuncMed->addColl(pDispColl);
	pDispMed->addColl(pFuncColl);

	cout << "Func Send: " << "Add Value" << endl;
	pFuncColl->sendMsg("Add Value");
	cout << "Display Send: " << "Show Result" << endl;
	pDispColl->sendMsg("Show Result");

	delete pFuncColl;
	delete pDispColl;
	delete pFuncMed;
	delete pDispMed;
}