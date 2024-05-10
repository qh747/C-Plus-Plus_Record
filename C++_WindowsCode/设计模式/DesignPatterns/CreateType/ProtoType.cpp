#include "ProtoType.h"

AbstractProtoType* FirstSpecificProtoType::clone()
{
	FirstSpecificProtoType* pFstSpecific = new FirstSpecificProtoType();
	pFstSpecific->setTitle(this->m_title);
	pFstSpecific->setInfo(this->m_Info);

	return pFstSpecific;
}

AbstractProtoType* SecondSpecificProtoType::clone()
{
	SecondSpecificProtoType* pFstSpecific = new SecondSpecificProtoType();
	pFstSpecific->setTitle(this->m_title);
	pFstSpecific->setInfo(this->m_Info);

	return pFstSpecific;
}

void ShowProtoType(AbstractProtoType* pAbstractProtoType)
{
	cout << "Title: " << pAbstractProtoType->getTitle() << endl;
	cout << "Info: " << pAbstractProtoType->getInfo() << endl;
}

void SetInfo(AbstractProtoType* pAbstractProtoType, const vector<string>& infoVec)
{
	for (int i = 0; i < infoVec.size(); ++i)
	{
		AbstractProtoType* pSpecific = pAbstractProtoType->clone();
		pSpecific->setInfo(infoVec[i]);

		ShowProtoType(pSpecific);
	}
}

void ProtoTypeTestDemo()
{
	vector<string> InfoArray;
	InfoArray.push_back(string("Info A"));
	InfoArray.push_back(string("Info B"));
	InfoArray.push_back(string("Info C"));

	AbstractProtoType* pFstProtoType = new FirstSpecificProtoType();
	pFstProtoType->setTitle(string("First"));
	SetInfo(pFstProtoType, InfoArray);

	AbstractProtoType* pSecProtoType = new FirstSpecificProtoType();
	pSecProtoType->setTitle(string("Second"));
	SetInfo(pSecProtoType, InfoArray);

	delete pFstProtoType;
	delete pSecProtoType;
}