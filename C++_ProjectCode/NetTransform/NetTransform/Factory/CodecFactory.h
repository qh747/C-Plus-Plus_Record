#pragma once
#include "../Protobuf/Codec.h"
#include "../PublicDataDef/PublicDataDef.h"

class CodecFactory
{
public:
	CodecFactory();
	virtual					~CodecFactory();

public:
	virtual Codec_Base*		createCodec() = 0;
	virtual void			modifyType(Serial_t type, void* pModData) = 0;

protected:
	void					setType(Serial_t type);
	Serial_t				getType();

private:
	Serial_t				m_serialType;
};