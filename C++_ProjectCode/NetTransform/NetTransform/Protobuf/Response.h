#pragma once
#include "Codec.h"
#include "Message.pb.h"
#include "ProtobufDataDef.h"

class Response_Codec : public Codec_Base
{
public:
	Response_Codec();
	Response_Codec(const std::string& encStr);			// 用于解码
	Response_Codec(const ResponseMsg_dt& respStr);		// 用于编码
	virtual ~Response_Codec();

public:
	void initMessage(const std::string& encStr);		// 用于解码，前提使用默认空构造函数
	void initMessage(const ResponseMsg_dt& respStr);	// 用于编码，前提使用默认空构造函数

public:
	virtual std::string encodeMsg();					// 用于序列化
	virtual void*       decodeMsg();					// 用于反序列化

private:
	std::string		 m_str;
	ResponseMessage  m_msg;
};