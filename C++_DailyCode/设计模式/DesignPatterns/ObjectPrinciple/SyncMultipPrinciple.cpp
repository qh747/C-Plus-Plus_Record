#include "SyncMultipPrinciple.h"

void Person::buyCar(const string& carName, int size)
{
	if (nullptr != m_pCar)
		delete m_pCar;

	if (size < 100)
		m_pCar = new SmallCar(carName);
	else
		m_pCar = new BigCar(carName);
}

void Person::useCar()
{
	cout << "Person Drive " << m_pCar->getCarName() << endl;
}

void SyncMultipPrincipleTestDemo()
{
	Person personObj;
	personObj.buyCar("A1", 10);
	personObj.useCar();

	personObj.buyCar("B1", 100);
	personObj.useCar();
}