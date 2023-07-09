#include "ReqCodecFactory.h"

ReqCodecFactory::ReqCodecFactory(const string& serialData)
{
	this->setType(SERIAL_TYPE);
	m_serialData = serialData;
}

ReqCodecFactory::ReqCodecFactory(const RequestMsg_dt& data)
{
	this->setType(UNSERIAL_TYPE);
	m_originData = data;
}

ReqCodecFactory::~ReqCodecFactory()
{
}

Codec_Base* ReqCodecFactory::createCodec()
{
	Codec_Base* pCodec = NULL;

	if (SERIAL_TYPE == this->getType())
		pCodec = new Request_Codec(m_serialData);
	else if(UNSERIAL_TYPE == this->getType())
		pCodec = new Request_Codec(m_originData);

	return pCodec;
}

void ReqCodecFactory::modifyType(Serial_t type, void* pModData)
{
	if (SERIAL_TYPE == type)
		m_serialData = *(static_cast<string *>(pModData));
	else if (UNSERIAL_TYPE == type)
		m_originData = *(static_cast<RequestMsg_dt *>(pModData));

	this->setType(type);
}