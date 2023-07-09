#include "CodecFactory.h"

CodecFactory::CodecFactory()
{
}

CodecFactory::~CodecFactory()
{
}

void CodecFactory::setType(Serial_t type)
{
	m_serialType = type;
}

Serial_t CodecFactory::getType()
{
	return m_serialType;
}