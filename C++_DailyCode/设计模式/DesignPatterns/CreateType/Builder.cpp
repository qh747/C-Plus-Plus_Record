#include "Builder.h"

void EthBuilder::buildMsgHead(MsgHeader_dt head)
{
	stringstream ss;
	ss << "Ethernet Msg Head: " << head.msgType << " " << head.msgId;
	m_msgContent.append(ss.str());
}

void EthBuilder::buildMsgData(MsgData_dt data)
{
	stringstream ss;
	ss << " Ethernet Msg Data: " << data.msgData << " " << data.msgSize;
	m_msgContent.append(ss.str());
}

void IPBuilder::buildMsgHead(MsgHeader_dt head)
{
	stringstream ss;
	ss << "IP Msg Head: " << head.msgType << " " << head.msgId;
	m_msgContent.append(ss.str());
}

void IPBuilder::buildMsgData(MsgData_dt data)
{
	stringstream ss;
	ss << " IP Msg Data: " << data.msgData << " " << data.msgSize;
	m_msgContent.append(ss.str());
}

AbstractBuilder* Director::replaceBuilder(AbstractBuilder* other)
{
	AbstractBuilder* pOldBuilder = m_msgBuilder;
	m_msgBuilder = other;
	return pOldBuilder;
}

void Director::constructMsg(Msg_t type, int id, const string& data, int size)
{
	m_msgBuilder->buildMsgHead(MsgHeader_dt{ type, id });
	m_msgBuilder->buildMsgData(MsgData_dt{ data , size });
}

void BuilderTestDemo()
{
	Director director = Director(new EthBuilder());
	director.constructMsg(ETH_MESG_TYPE, 1, "Ethernet Data.", strlen("Ethernet Data."));
	cout << director.getMsg() << endl;

	delete director.replaceBuilder(new IPBuilder());

	director.constructMsg(IP_MESG_TYPE, 2, "IP Data.", strlen("IP Data."));
	cout << director.getMsg() << endl;
}