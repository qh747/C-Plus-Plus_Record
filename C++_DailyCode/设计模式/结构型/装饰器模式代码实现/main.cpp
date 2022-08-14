#include <iostream>
#include <cstring>
#include <string>
#include <memory>
using namespace std;

/*抽象流类    **/
class AbstractStream
{
public:
	virtual ~AbstractStream() { }

public:
	virtual string read(void)           = 0;
	virtual void   write(string stream) = 0;
};

/*文件流类    **/
class FileStream : public AbstractStream
{
public:
	FileStream() { }
	virtual ~FileStream() { }

public:
	virtual string read(void)
	{
		return string("File Stream.");
	}

	virtual void write(string stream)
	{
		cout << "File Write: " << stream << endl;
	}
};

/*网络流类    **/
class NetworkStream : public AbstractStream
{
public:
	NetworkStream() { }
	virtual ~NetworkStream() { }

public:
	virtual string read(void)
	{
		return string("Network Stream.");
	}

	virtual void write(string stream)
	{
		cout << "Network Write: " << stream << endl;
	}
};

/*抽象装饰器类    **/
class AbstractDecorator : public AbstractStream
{
public:
	AbstractDecorator(AbstractStream* stream) : m_streamPtr(stream)
	{

	}

	virtual ~AbstractDecorator()
	{

	}

public:
	virtual string read(void)
	{
		return m_streamPtr->read();
	}

	virtual void write(string stream)
	{
		m_streamPtr->write(stream);
	}

private:
	AbstractStream* m_streamPtr;
};

/*加密装饰器类    **/
class encryptClass : public AbstractDecorator
{
public:
	encryptClass(AbstractStream* stream) : AbstractDecorator(stream)
	{

	}

	virtual ~encryptClass()
	{

	}

public:
	virtual string read(void)
	{
		string srcStreamStr = AbstractDecorator::read();

		string encryptStreamStr = string("<encrypt> ") + srcStreamStr;		/*加了<>符号表示原始流经过的处理方法    **/
		return encryptStreamStr;
	}

	virtual void write(string stream)
	{
		string encryptStr = string("<encrypt> ") + stream;
		AbstractDecorator::write(encryptStr);
	}
};

/*压缩装饰器类    **/
class CompressClass : public AbstractDecorator
{
public:
	CompressClass(AbstractStream* stream) : AbstractDecorator(stream)
	{

	}

	virtual ~CompressClass()
	{

	}

public:
	virtual string read(void)
	{
		string srcStreamStr = AbstractDecorator::read();

		string compressStreamStr = string("<compress> ") + srcStreamStr;
		return compressStreamStr;
	}

	virtual void write(string stream)
	{
		string compresstStr = string("<compress> ") + stream;
		AbstractDecorator::write(compresstStr);
	}
};

int main()
{
	/*原始流文件读入    **/
	shared_ptr<AbstractStream> streamPtr = make_shared<FileStream>();
	cout << streamPtr->read() << endl;

	/*加密装饰器装饰文件流, 进行文件流加密、读入操作    **/
	shared_ptr<AbstractDecorator> encryptPtr = make_shared<encryptClass>(streamPtr.get());	
	cout << encryptPtr->read() << endl;

	/*压缩装饰器类装饰加密装饰器, 进行文件流压缩、加密、读入操作    **/
	shared_ptr<AbstractDecorator> encryptCompressPtr = make_shared<CompressClass>(encryptPtr.get());
	cout << encryptCompressPtr->read() << endl;

	system("pause");
	return 0;
}