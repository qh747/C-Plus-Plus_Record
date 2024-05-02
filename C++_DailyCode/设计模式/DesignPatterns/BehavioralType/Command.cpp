#include "Command.h"

Reciver::~Reciver()
{
	if (!m_playerMap.empty())
	{
		map<int, Player_dt*>::iterator iter = m_playerMap.begin();
		while (iter != m_playerMap.end())
		{
			delete iter->second;
			iter = m_playerMap.erase(iter);
		}
	}
}

void Reciver::addPlayer(const Player_dt& player)
{
	if (m_playerMap.end() == m_playerMap.find(player.iId))
		m_playerMap.insert(std::make_pair(player.iId, new Player_dt(player)));
}

void Reciver::modifyAttack(int id, int attack)
{
	map<int, Player_dt*>::iterator iter = m_playerMap.find(id);
	if (m_playerMap.end() != iter)
		iter->second->dAttack = attack;
}

void Reciver::modifyBlood(int id, int blood)
{
	map<int, Player_dt*>::iterator iter = m_playerMap.find(id);
	if (m_playerMap.end() != iter)
		iter->second->dBlood = blood;
}

void Reciver::showPlayer(int id)
{
	map<int, Player_dt*>::iterator iter = m_playerMap.find(id);
	if (m_playerMap.end() != iter)
		cout << "ID: " << iter->second->iId << " ATT: " << iter->second->dAttack << " BLD: " << iter->second->dBlood << endl;
}

void AttackCommand::execute(int id, void* attribute)
{
	int* attack = static_cast<int *>(attribute);
	Reciver* pRecv = this->getReceiver();
	pRecv->modifyAttack(id, *attack);
}

void BloodCommand::execute(int id, void* attribute)
{
	int* blood = static_cast<int *>(attribute);
	Reciver* pRecv = this->getReceiver();
	pRecv->modifyBlood(id, *blood);
}

Invoker::~Invoker()
{
	while (!m_cmdQueue.empty())
	{
		delete m_cmdQueue.front();
		m_cmdQueue.pop();
	}
}

void Invoker::pushCommand(Command* cmd, int id, void* attr)
{
	Command_dt* cmdStruct = new Command_dt(cmd, id, attr);
	m_cmdQueue.push(cmdStruct);
}

void Invoker::executeCmd()
{
	while (!m_cmdQueue.empty())
	{
		Command_dt* pTopCmd = m_cmdQueue.front();
		pTopCmd->pCmd->execute(pTopCmd->iId, pTopCmd->pAttr);
		m_cmdQueue.pop();
	}
}

void CommandTestDemo()
{
	Reciver recv;
	recv.addPlayer(Reciver::Player_dt(1));
	recv.addPlayer(Reciver::Player_dt(2));

	Invoker cmdCache;

	int attackVal = 10;
	Command* attack = new AttackCommand();
	attack->setReceiver(&recv);
	cmdCache.pushCommand(attack, 1, &attackVal);
	
	int bloodVal = 90;
	Command* blood = new BloodCommand();
	blood->setReceiver(&recv);
	cmdCache.pushCommand(blood, 2, &bloodVal);

	cmdCache.executeCmd();
	recv.showPlayer(1);
	recv.showPlayer(2);

	delete attack;
	delete blood;
}