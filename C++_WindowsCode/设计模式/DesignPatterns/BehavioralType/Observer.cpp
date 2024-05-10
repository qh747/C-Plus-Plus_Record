#include "Observer.h"

void NewsTopic::subscribe(AbstractObserver* observerPtr)
{
	if (m_observerArray.end() == std::find(m_observerArray.begin(), m_observerArray.end(), observerPtr))
		m_observerArray.push_back(observerPtr);
}

void NewsTopic::publish(const string& data)
{
	for (vector<AbstractObserver*>::iterator iter = m_observerArray.begin(); iter != m_observerArray.end(); ++iter)
	{
		(*iter)->update("News Topic: " + data);
	}
}

void ObserverTestDemo()
{
	AbstractObserver* pPhoneObserv = new PhoneObserver();
	AbstractObserver* pComputerObserv = new ComputerObserver();

	AbstractTopic* pNews = new NewsTopic();
	pNews->subscribe(pPhoneObserv);
	pNews->subscribe(pComputerObserv);

	pNews->publish("Today Is 2024.04.25");
	delete pPhoneObserv;
	delete pComputerObserv;
	delete pNews;
}