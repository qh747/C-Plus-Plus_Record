#include "Memento.h"

void MementoTestDemo()
{
	Originator origin("INIT_STATE");
	cout << "Init: " << origin.getState() << endl;

	CareTaker memManager;
	memManager.addMemento(origin.saveState());

	origin.setState("RUN_STATE");
	cout << "Run: " << origin.getState() << endl;
	memManager.addMemento(origin.saveState());

	origin.setState("END_STATE");
	cout << "End: " << origin.getState() << endl;

	while (memManager.hasMemento())
	{
		Memento* lastMem = memManager.getLastMemento();
		origin.restoreState(*lastMem);

		cout << "Rollback£º" << origin.getState() << endl;
		delete lastMem;
	}
}