#pragma once
#include "CodecFactory.h"
#include "../Protobuf/Response.h"

class RespCodecFactory : public CodecFactory
{
public:
	RespCodecFactory(const string& serialData);								// 响应消息构造，用于接下来创建反序列化的数据
	RespCodecFactory(const ResponseMsg_dt& data);							// 响应消息构造，用于接下来创建序列化的数据
	virtual ~RespCodecFactory();

public:
	virtual Codec_Base* createCodec();										// 创建数据	
	virtual void		modifyType(Serial_t type, void* pModData);			// 修改数据类型

private:
	string				m_serialData;										// 序列化后的数据
	ResponseMsg_dt		m_originData;										// 原始数据
};