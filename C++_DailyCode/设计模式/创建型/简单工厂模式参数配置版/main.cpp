#include <iostream>
#include <cstring>
#include <string>
#include "AutoFactory.h"
using namespace std;

int main()
{
	AbstractResObjClass* absResObjClsPtr = AutoFactory::createOne();
	if (NULL != absResObjClsPtr)
		absResObjClsPtr->showData("Hello World.");

	delete absResObjClsPtr;

	system("pause");
	return 0;
}