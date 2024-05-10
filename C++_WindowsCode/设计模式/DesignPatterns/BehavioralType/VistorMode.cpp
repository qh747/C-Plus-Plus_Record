#include "VistorMode.h"

void VistorTestDemo()
{
	// 组合类创建
	Computer* computer = new Computer();

	// 访问者类创建
	Vistor* simpVistor = new SimpleChecker();
	Vistor* highVistor = new HighChecker();

	// 访问者访问元素
	computer->accept(simpVistor);
	computer->accept(highVistor);

	delete computer;
}