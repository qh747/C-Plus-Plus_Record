#include <iostream>
#include <cstring>
#include <string>
using namespace std;

/*子系统组件类    **/
class FileSystem
{
public:
	void start()
	{
		cout << "File System Start." << endl;
	}

	void close()
	{
		cout << "File System Close." << endl;
	}
};

class IOSystem
{
public:
	void start()
	{
		cout << "IO System Start." << endl;
	}

	void close()
	{
		cout << "IO System Close." << endl;
	}
};

class BlackWindowSystem
{
public:
	void start()
	{
		cout << "BlackWindow System Start." << endl;
	}

	void close()
	{
		cout << "BlackWindow System Close." << endl;
	}
};

class GraphicsWindowSystem
{
public:
	void start()
	{
		cout << "GraphicsWindow System Start." << endl;
	}

	void close()
	{
		cout << "GraphicsWindow System Close." << endl;
	}
};

/*普通外观类    **/
class SimpleFacade
{
public:
	SimpleFacade()
	{
		m_filePtr = new FileSystem();
		m_ioPtr = new IOSystem();
		m_graphicsPtr = new GraphicsWindowSystem();
	}

	~SimpleFacade()
	{
		delete m_filePtr;
		m_filePtr = NULL;

		delete m_ioPtr;
		m_ioPtr = NULL;

		delete m_graphicsPtr;
		m_graphicsPtr = NULL;
	}

public:
	void start()
	{
		m_filePtr->start();
		m_ioPtr->start();
		m_graphicsPtr->start();
	}

	void close()
	{
		m_filePtr->close();
		m_ioPtr->close();
		m_graphicsPtr->close();
	}

private:
	FileSystem* m_filePtr;
	IOSystem* m_ioPtr;
	GraphicsWindowSystem* m_graphicsPtr;
};

/*抽象外观类    **/
class AbstractFacade
{
public:
	virtual ~AbstractFacade() { }

public:
	virtual void start() = 0;
	virtual void close() = 0;
};

/*黑窗口外观类    **/
class BlackWindowFacade : public AbstractFacade
{
public:
	BlackWindowFacade()
	{
		m_filePtr = new FileSystem();
		m_ioPtr = new IOSystem();
		m_windowPtr = new BlackWindowSystem();
	}

	virtual ~BlackWindowFacade()
	{
		delete m_filePtr;
		m_filePtr = NULL;

		delete m_ioPtr;
		m_ioPtr = NULL;

		delete m_windowPtr;
		m_windowPtr = NULL;
	}

public:
	virtual void start()
	{
		m_filePtr->start();
		m_ioPtr->start();
		m_windowPtr->start();
	}

	virtual void close()
	{
		m_filePtr->close();
		m_ioPtr->close();
		m_windowPtr->close();
	}

private:
	FileSystem* m_filePtr;
	IOSystem* m_ioPtr;
	BlackWindowSystem* m_windowPtr;
};


/*图形窗口外观类    **/
class GraphicsWindowFacade : public AbstractFacade
{
public:
	GraphicsWindowFacade()
	{
		m_filePtr = new FileSystem();
		m_ioPtr = new IOSystem();
		m_windowPtr = new GraphicsWindowSystem();
	}

	virtual ~GraphicsWindowFacade()
	{
		delete m_filePtr;
		m_filePtr = NULL;

		delete m_ioPtr;
		m_ioPtr = NULL;

		delete m_windowPtr;
		m_windowPtr = NULL;
	}

public:
	virtual void start()
	{
		m_filePtr->start();
		m_ioPtr->start();
		m_windowPtr->start();
	}

	virtual void close()
	{
		m_filePtr->close();
		m_ioPtr->close();
		m_windowPtr->close();
	}

private:
	FileSystem* m_filePtr;
	IOSystem* m_ioPtr;
	GraphicsWindowSystem* m_windowPtr;
};

int main()
{
	/*普通外观类使用    **/
	SimpleFacade simpleFacadeObj;
	simpleFacadeObj.start();
	simpleFacadeObj.close();

	/*抽象外观类使用    **/
	AbstractFacade* facadePtr = new BlackWindowFacade();
	facadePtr->start();
	facadePtr->close();

	delete facadePtr;
	facadePtr = NULL;

	facadePtr = new GraphicsWindowFacade();
	facadePtr->start();
	facadePtr->close();

	delete facadePtr;
	facadePtr = NULL;

	system("pause");
	return 0;
}