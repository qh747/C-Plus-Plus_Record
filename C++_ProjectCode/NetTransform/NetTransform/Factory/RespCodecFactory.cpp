#include "RespCodecFactory.h"

RespCodecFactory::RespCodecFactory(const string& serialData)
{
	this->setType(SERIAL_TYPE);
	m_serialData = serialData;
}

RespCodecFactory::RespCodecFactory(const ResponseMsg_dt& data)
{
	this->setType(UNSERIAL_TYPE);
	m_originData = data;
}

RespCodecFactory::~RespCodecFactory()
{
}

Codec_Base* RespCodecFactory::createCodec()
{
	Codec_Base* pCodec = NULL;

	if (SERIAL_TYPE == this->getType())
		pCodec = new Response_Codec(m_serialData);
	else if (UNSERIAL_TYPE == this->getType())
		pCodec = new Response_Codec(m_originData);

	return pCodec;
}

void RespCodecFactory::modifyType(Serial_t type, void* pModData)
{
	if (SERIAL_TYPE == type)
		m_serialData = *(static_cast<string *>(pModData));
	else if (UNSERIAL_TYPE == type)
		m_originData = *(static_cast<ResponseMsg_dt *>(pModData));

	this->setType(type);
}