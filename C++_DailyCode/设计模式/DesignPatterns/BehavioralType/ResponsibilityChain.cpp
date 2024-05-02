#include "ResponsibilityChain.h"

void IPMsgHandler::recvMsg(const Msg_dt& msg)
{
	cout << "Process Part Of IP Layer: " << msg.ipMsg << endl;
	
	AbstractMsgHandler* handler = this->getNextHandler();
	if (nullptr != handler)
		handler->recvMsg(msg);
}

void TransMsgHandler::recvMsg(const Msg_dt& msg)
{
	cout << "Process Part Of Transport Layer: " << msg.transMsg << endl;

	AbstractMsgHandler* handler = this->getNextHandler();
	if (nullptr != handler)
		handler->recvMsg(msg);
}

void APPMsgHandler::recvMsg(const Msg_dt& msg)
{
	cout << "Process Part Of APP Layer: " << msg.appMsg << endl;

	AbstractMsgHandler* handler = this->getNextHandler();
	if (nullptr != handler)
		handler->recvMsg(msg);
}

void RespChainTestDemo()
{
	AbstractMsgHandler* ipHandler = new IPMsgHandler();
	AbstractMsgHandler* transHandler = new TransMsgHandler();
	AbstractMsgHandler* appHandler = new APPMsgHandler();

	ipHandler->setNextHandler(transHandler);
	transHandler->setNextHandler(appHandler);

	Msg_dt msg;
	msg.ipMsg = "Src IP: 192.168.0.1; Dst IP: 192.168.0.10";
	msg.transMsg = "Src Port: 1025; Dst Port: 80";
	msg.appMsg = "Voice Msg...";

	ipHandler->recvMsg(msg);

	delete appHandler;
	delete transHandler;
	delete ipHandler;
}