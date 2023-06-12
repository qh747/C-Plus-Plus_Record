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
	m_msg.set_sign(reqStr.sign);
	m_msg.set_cmdtype(reqStr.cmdType);
	m_msg.set_clientid(reqStr.clientId);
	m_msg.set_serverid(reqStr.serverId);
	m_msg.set_data(reqStr.data);
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
	pDecodeResult->clientId = m_msg.clientid();
	pDecodeResult->cmdType = m_msg.cmdtype();
	pDecodeResult->data = m_msg.data();
	pDecodeResult->serverId = m_msg.serverid();
	pDecodeResult->sign = m_msg.sign();

	return pDecodeResult;
}