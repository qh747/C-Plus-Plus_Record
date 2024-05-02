#include "StateMode.h"

void StateTestDemo()
{
	AbstractState* sStat = new SendState();
	AbstractState* rStat = new RecvState();
	Context cont;

	// 切换为发送状态
	cont.setState(sStat);
	cont.handleData("Network Data");

	// 切换为接收状态
	cont.setState(rStat);
	cont.handleData("Network Data");

	delete sStat;
	delete rStat;
}