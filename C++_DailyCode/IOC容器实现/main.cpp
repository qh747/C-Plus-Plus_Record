#include "IocContainer.h"
using namespace std;

int main()
{
	IocContainer<AbstractClass> iocContainer;
	/*注册一号派生类和二号派生类    **/
	iocContainer.registerType<FirstInheritClass>("FirstInheritClass");
	iocContainer.registerType<SecondInheritClass>("SecondInheritClass");

	shared_ptr<AbstractClass> fstSharedPtr = iocContainer.resolve("FirstInheritClass");
	if (NULL != fstSharedPtr)
		fstSharedPtr->showStr("HELLO");

	fstSharedPtr = iocContainer.resolve("SecondInheritClass");
	if (NULL != fstSharedPtr)
		fstSharedPtr->showStr("BYE");

	system("pause");
	return 0;
}