#pragma once
#include "CodecFactory.h"
#include "../Protobuf/Request.h"

class ReqCodecFactory : public CodecFactory
{
public:
	ReqCodecFactory(const string& serialData);								// 请求消息构造，用于接下来创建反序列化的数据
	ReqCodecFactory(const RequestMsg_dt& data);								// 请求消息构造，用于接下来创建序列化的数据
	virtual ~ReqCodecFactory();

public:
	virtual Codec_Base* createCodec();										// 创建数据	
	virtual void		modifyType(Serial_t type, void* pModData);			// 修改数据类型
		
private:
	string				m_serialData;										// 序列化后的数据
	RequestMsg_dt		m_originData;										// 原始数据
};