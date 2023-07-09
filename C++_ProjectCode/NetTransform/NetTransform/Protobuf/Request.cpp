#include "Request.h"

Request_Codec::Request_Codec()
{
}

Request_Codec::Request_Codec(const std::string& encStr)
{
	this->initMessage(encStr);
}

Request_Codec::Request_Codec(const RequestMsg_dt& reqStr)
{
	this->initMessage(reqStr);
}

Request_Codec::~Request_Codec()
{
}

void Request_Codec::initMessage(const std::string& encStr)
{
	m_str = encStr;
}

void Request_Codec::initMessage(const RequestMsg_dt& reqStr)
{
	m_msg.set_sign(reqStr.sSign);
	m_msg.set_cmdtype(reqStr.iCmdType);
	m_msg.set_clientid(reqStr.sClientId);
	m_msg.set_serverid(reqStr.sServerId);
	m_msg.set_data(reqStr.sData);
}

std::string Request_Codec::encodeMsg()
{
	m_msg.SerializeToString(&m_str);
	return m_str;
}

void* Request_Codec::decodeMsg()
{
	RequestMsg_dt* pDecodeResult = new RequestMsg_dt();
	m_msg.ParseFromString(m_str);
	pDecodeResult->sClientId	= m_msg.clientid();
	pDecodeResult->iCmdType		= m_msg.cmdtype();
	pDecodeResult->sData		= m_msg.data();
	pDecodeResult->sServerId	= m_msg.serverid();
	pDecodeResult->sSign		= m_msg.sign();

	return pDecodeResult;
}