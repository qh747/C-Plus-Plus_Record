#include "Bridging.h"

void BrandFstComputer::installSystem(AbstractSystem* osPtr)
{
	m_osPtr = osPtr;

	cout << "BrandFst Computer Open." << endl;
	cout << "System Installing..." << endl;
	m_osPtr->operation();
	cout << "System Install Done." << endl << endl;
}

void BrandFstComputer::reinstallSystem(AbstractSystem* osPtr)
{
	m_osPtr = nullptr;
	cout << "BrandFst Computer Close." << endl;
	cout << "System Clear..." << endl;

	this->installSystem(osPtr);
}

void BridgingModeTestDemo()
{
	AbstractSystem* pWinSys = new WindowsSystem();
	AbstractSystem* pLinuxSys = new LinuxSystem();

	AbstractComputer* pComputer = new BrandFstComputer();
	pComputer->installSystem(pWinSys);
	pComputer->reinstallSystem(pLinuxSys);

	delete pComputer;
	delete pWinSys;
	delete pLinuxSys;
}