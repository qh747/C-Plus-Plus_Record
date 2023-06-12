#include "Response.h"

Response_Codec::Response_Codec()
{

}

Response_Codec::Response_Codec(const std::string& encStr)
{
	this->initMessage(encStr);
}

Response_Codec::Response_Codec(const ResponseMsg_dt& respStr)
{
	this->initMessage(respStr);
}

Response_Codec::~Response_Codec()
{

}

void Response_Codec::initMessage(const std::string& encStr)
{
	m_str = encStr;
}

void Response_Codec::initMessage(const ResponseMsg_dt& respStr)
{
	m_msg.set_clientid(respStr.clientId);
	m_msg.set_data(respStr.data);
	m_msg.set_seckeyid(respStr.seckeyId);
	m_msg.set_serverid(respStr.serverId);
	m_msg.set_status(respStr.status);
}

std::string Response_Codec::encodeMsg()
{
	m_msg.SerializeToString(&m_str);
	return m_str;
}

void* Response_Codec::decodeMsg()
{
	ResponseMsg_dt* pDecodeResult = new ResponseMsg_dt();
	m_msg.ParseFromString(m_str);
	pDecodeResult->clientId = m_msg.clientid();
	pDecodeResult->seckeyId = m_msg.seckeyid();
	pDecodeResult->data = m_msg.data();
	pDecodeResult->serverId = m_msg.serverid();
	pDecodeResult->status = m_msg.status();

	return pDecodeResult;
}