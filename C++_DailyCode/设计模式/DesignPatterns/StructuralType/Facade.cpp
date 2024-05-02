#include "Facade.h"

void Facade::start()
{
	m_pFileSys->startFileSystem();
	m_pIOSys->startIOSystem();
	m_pGraphWinSys->startGraphWindowSystem();
}

void Facade::close()
{
	m_pFileSys->closeFileSystem();
	m_pIOSys->closeIOSystem();
	m_pGraphWinSys->closeGraphWindowSystem();
}

void FacadeTestDemo()
{
	FileSystem* pFile = new FileSystem();
	IOSystem* pIo = new IOSystem();
	GraphWindowSystem* pGraphWin = new GraphWindowSystem();

	Facade pFacade(pFile, pIo, pGraphWin);
	// 用户调用外观类的启动函数同时启动所有子系统
	pFacade.start();
	// 用户调用外观类的关闭函数同时关闭所有子系统
	pFacade.close();
	
	delete pFile;
	delete pIo;
	delete pGraphWin;
}