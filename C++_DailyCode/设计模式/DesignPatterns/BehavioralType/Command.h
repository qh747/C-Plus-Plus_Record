#pragma once
#include <iostream>
#include <string>
#include <map>
#include <queue>
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::queue;

// 接收方
class Reciver
{
public:
	typedef struct PLAYER_DATA_TYPE
	{
		int		iId;
		double	dAttack;
		double	dBlood;

		PLAYER_DATA_TYPE(int id)
		{
			iId = id;
			dAttack = 0;
			dBlood = 100;
		}
	}Player_dt;

public:
	~Reciver();
	void addPlayer(const Player_dt& player);
	void modifyAttack(int id, int attack);
	void modifyBlood(int id, int blood);
	void showPlayer(int id);

private:
	map<int, Player_dt*> m_playerMap;
};

// 命令模式
class Command
{
public:
	virtual ~Command() {}
	virtual void setReceiver(Reciver* pRecv) { m_pRecv = pRecv; }
	virtual Reciver* getReceiver() { return m_pRecv; }
	virtual void execute(int id, void* attribute) = 0;

private:
	Reciver* m_pRecv;
};

class AttackCommand : public Command
{
public:
	virtual ~AttackCommand() {}
	virtual void execute(int id, void* attr);
};

class BloodCommand : public Command
{
public:
	virtual ~BloodCommand() {}
	virtual void execute(int id, void* attr);
};

class Invoker
{
public:
	typedef struct COMMAND_DATA_TYPE
	{
		Command* pCmd;
		int iId;
		void* pAttr;

		COMMAND_DATA_TYPE(Command* cmd, int i, void* attr)
		{
			pCmd = cmd;
			iId = i;
			pAttr = attr;
		}
	}Command_dt;

public:
	~Invoker();
	void pushCommand(Command* cmd, int id, void* attr);
	void executeCmd();

private:
	queue<Command_dt*> m_cmdQueue;
};

// 命令模式测试函数
void CommandTestDemo();