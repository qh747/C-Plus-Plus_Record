#include "ThreadSingleton.h"

ThreadSingleton* ThreadSingleton::pInstance = nullptr;
mutex ThreadSingleton::InstanceLock;

ThreadSingleton* ThreadSingleton::getInstance()
{
	static ThreadSingletonRelease relsObj;

	if (nullptr == pInstance)
	{
		InstanceLock.lock();
		if(nullptr == pInstance)
			pInstance = new ThreadSingleton();
		InstanceLock.unlock();
	}
		
	return pInstance;
}

ThreadSingleton::ThreadSingletonRelease::~ThreadSingletonRelease()
{
	if (nullptr != pInstance)
		delete pInstance;
}

void ThreadSingletonTestDemo()
{
	thread fstThread(ThreadSingletonTask);
	thread secThread(ThreadSingletonTask);

	fstThread.join();
	secThread.join();
}

void ThreadSingletonTask()
{
	ThreadSingleton* pInc = ThreadSingleton::getInstance();
	for (int i = 1; i < 4; ++i)
	{
		pInc->setCount(i);
		cout << "Current: " << pInc->getCount() << endl;

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}