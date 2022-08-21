#include <iostream>
#include <memory>
#include <cstring>
#include <string>
using namespace std;

/*抽象操作系统类    **/
class AbstractOperatorSystem
{
public:
	virtual ~AbstractOperatorSystem() { }

public:
	virtual void operation() = 0;
};

class WindowsSystem : public AbstractOperatorSystem
{
public:
	WindowsSystem() { }
	virtual ~WindowsSystem() { }

public:
	virtual void operation()
	{
		cout << "Windows System Run." << endl;
	}
};

class LinuxSystem : public AbstractOperatorSystem
{
public:
	LinuxSystem() { }
	virtual ~LinuxSystem() { }

public:
	virtual void operation()
	{
		cout << "Linux System Run." << endl;
	}
};


/*抽象电脑类    **/
class AbstractComputer
{
public:
	AbstractComputer() : m_osPtr(NULL) { }
	virtual ~AbstractComputer() { }

public:
	virtual void installSystem(AbstractOperatorSystem* osPtr) = 0;

protected:
	AbstractOperatorSystem* m_osPtr;
};

class LenovoComputer : public AbstractComputer
{
public:
	LenovoComputer() : AbstractComputer() { }
	virtual ~LenovoComputer() { }

public:
	virtual void installSystem(AbstractOperatorSystem* osPtr)
	{
		m_osPtr = osPtr;

		cout << "Lenovo Computer Open." << endl;
		cout << "System Installing..." << endl;
		this->m_osPtr->operation();
		cout << "System Install Done." << endl << endl;
	}
};

class DellComputer : public AbstractComputer
{
public:
	DellComputer() : AbstractComputer() { }
	virtual ~DellComputer() { }

public:
	virtual void installSystem(AbstractOperatorSystem* osPtr)
	{
		m_osPtr = osPtr;

		cout << "Dell Computer Open." << endl;
		cout << "System Installing..." << endl;
		this->m_osPtr->operation();
		cout << "System Install Done." << endl << endl;
	}
};

int main()
{
	/*使用一台装有Windows系统的Lenovo电脑    **/
	AbstractOperatorSystem* pSystem = new WindowsSystem();
	AbstractComputer* pComputer = new LenovoComputer();

	pComputer->installSystem(pSystem);
	delete pSystem;

	/*使用一台装有Linux系统的Lenovo电脑    **/
	pSystem = new LinuxSystem();

	pComputer->installSystem(pSystem);
	delete pSystem;

	delete pComputer;

	/*使用一台装有Windows系统的Dell电脑    **/
	pSystem = new WindowsSystem();
	pComputer = new DellComputer();

	pComputer->installSystem(pSystem);
	delete pSystem;

	/*使用一台装有Linux系统的Lenovo电脑    **/
	pSystem = new LinuxSystem();

	pComputer->installSystem(pSystem);

	delete pSystem;
	delete pComputer;

	system("pause");
	return 0;
}