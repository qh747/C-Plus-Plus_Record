#include "LazySingleton.h"

LazySingleton* LazySingleton::pInstance = nullptr;

LazySingleton* LazySingleton::getInstance()
{
	static LazySingletonRelease relsObj;

	// 懒汉式单例模式对象于程序运行期间创建
	if (nullptr == pInstance)
		pInstance = new LazySingleton();
	return pInstance;
}

LazySingleton::LazySingletonRelease::~LazySingletonRelease()
{
	if (nullptr != pInstance)
		delete pInstance;
}

void LazySingletonTestDemo()
{
	LazySingleton* pInc = LazySingleton::getInstance();
	pInc->setCount(20);
	cout << "Current: " << pInc->getCount() << endl;
}