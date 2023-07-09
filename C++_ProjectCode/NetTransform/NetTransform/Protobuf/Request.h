#pragma once
#include "Codec.h"
#include "Message.pb.h"
#include "../PublicDataDef/PublicDataDef.h"

class Request_Codec : public Codec_Base
{
public:
	Request_Codec();
	Request_Codec(const std::string& encStr);			// 用于解码
	Request_Codec(const RequestMsg_dt& reqStr);			// 用于编码
	virtual ~Request_Codec();

public:
	void initMessage(const std::string& encStr);		// 用于解码，前提使用默认空构造函数
	void initMessage(const RequestMsg_dt& reqStr);		// 用于编码，前提使用默认空构造函数

public:
	virtual std::string encodeMsg();					// 用于序列化
	virtual void*       decodeMsg();					// 用于反序列化

private:
	std::string		m_str;
	RequestMessage  m_msg;
};