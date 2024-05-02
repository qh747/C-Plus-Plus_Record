#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

// 被装饰器类
class AbstractDataStream
{
public:
	virtual ~AbstractDataStream() { }
	virtual string read() = 0;
	virtual void write(string streamVal) = 0;

protected:
	string m_streamCache;
};

class FileStream : public AbstractDataStream
{
public:
	virtual ~FileStream() {}
	virtual string read(void) {	return "FILE STREAM: " + m_streamCache; }
	virtual void write(string streamVal) { m_streamCache = streamVal; }
};

class NetworkStream : public AbstractDataStream
{
public:
	virtual ~NetworkStream() {}
	virtual string read(void) {	return "NETWORK STREAM: " + m_streamCache; }
	virtual void write(string streamVal) { m_streamCache = streamVal; }
};

// 装饰器模式
class AbstractDecorator : public AbstractDataStream
{
public:
	AbstractDecorator(AbstractDataStream* streamVal) : m_streamPtr(streamVal) {}
	virtual ~AbstractDecorator() {}
	virtual string read(void) { return m_streamPtr->read(); }
	virtual void write(string streamVal) { m_streamPtr->write(streamVal); }
	virtual void replaceStream(AbstractDataStream* streamVal) { m_streamPtr = streamVal; }

private:
	AbstractDataStream* m_streamPtr;
};

class encryptDecorator : public AbstractDecorator
{
public:
	encryptDecorator(AbstractDataStream* streamVal) : AbstractDecorator(streamVal) {}
	virtual ~encryptDecorator() {}
	virtual string read(void);
	virtual void write(string streamVal);
};

class CompressDecorator : public AbstractDecorator
{
public:
	CompressDecorator(AbstractDataStream* streamVal) : AbstractDecorator(streamVal) {}
	virtual ~CompressDecorator() {}
	virtual string read(void);
	virtual void write(string streamVal);
};

// 装饰器模式测试函数
void DecoratorTestDemo();