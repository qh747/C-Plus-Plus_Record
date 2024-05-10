#include "RelyInersionPrinciple.h"

string ToUpperBottomLayer::doService(const string& data)
{
	string upperStr("");
	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i] >= 'a' && data[i] <= 'z') 
			upperStr += data[i] - 'a' + 'A';
		else 
			upperStr += data[i];
	}
	return upperStr;
}

string ToLowerBottomLayer::doService(const string& data)
{
	string lowerStr("");
	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i] >= 'A' &&data[i] <= 'Z') 
			lowerStr += data[i] - 'A' + 'a';
		else 
			lowerStr += data[i];
	}
	return lowerStr;
}

void DisplayFuncTopLayer(AbstractLayer* pProcMethod, const string& data)
{
	string procData = pProcMethod->doService(data);
	cout << "Before Process: " << data << endl;
	cout << "After Process: " << procData << endl;
}

void RelyOnInersionPrincipleTestDemo()
{
	AbstractLayer* pProcMethod = new ToUpperBottomLayer();
	DisplayFuncTopLayer(pProcMethod, "01234AbCdEfGhIjKlMnOpQrStUvWxYz56789");
	delete pProcMethod;

	pProcMethod = new ToLowerBottomLayer();
	DisplayFuncTopLayer(pProcMethod, "01234AbCdEfGhIjKlMnOpQrStUvWxYz56789");
	delete pProcMethod;
}