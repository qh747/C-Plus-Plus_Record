#pragma once
#include <iostream>
#include <sstream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

// 消息
typedef enum MSG_TYPE
{
	ETH_MESG_TYPE	= 1,
	IP_MESG_TYPE	= 2,

}Msg_t;

typedef struct MSG_HEADER
{
	Msg_t			msgType;
	int				msgId;

}MsgHeader_dt;

typedef struct MSG_DATA
{
	string			msgData;
	int				msgSize;
}MsgData_dt;

// 构建器模式
class AbstractBuilder
{
public:
	virtual ~AbstractBuilder() {}

public:
	virtual void	buildMsgHead(MsgHeader_dt head) = 0;
	virtual void	buildMsgData(MsgData_dt data) = 0;
	virtual string	getFormatMsg() = 0;

protected:
	string m_msgContent;
};

class EthBuilder : public AbstractBuilder
{
public:
	virtual ~EthBuilder() {}

public:
	virtual void	buildMsgHead(MsgHeader_dt head);
	virtual void	buildMsgData(MsgData_dt data);
	virtual string	getFormatMsg() { return m_msgContent; }
};

class IPBuilder : public AbstractBuilder
{
public:
	virtual ~IPBuilder() {}

public:
	virtual void	buildMsgHead(MsgHeader_dt head);
	virtual void	buildMsgData(MsgData_dt data);
	virtual string	getFormatMsg() { return m_msgContent; }
};

// 指导消息构建类
class Director
{
public:
	Director(AbstractBuilder* builder) :m_msgBuilder(builder) {}
	~Director()
	{
		if (NULL != m_msgBuilder)
			delete m_msgBuilder;
	}

public:
	AbstractBuilder*	replaceBuilder(AbstractBuilder* other);
	void				constructMsg(Msg_t type, int id, const string& data, int size);
	string				getMsg() { return m_msgBuilder->getFormatMsg(); }

private:
	AbstractBuilder* m_msgBuilder;
};

// 构建器模式测试函数
void BuilderTestDemo();