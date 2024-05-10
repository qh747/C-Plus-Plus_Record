#include "MyImportPkgTest.h"

/*protobufÊ¹ÓÃMyImportPkg²âÊÔº¯Êý					**/
void funcMyImportPkgTest()
{
	package::MyPackage pkg;

	pkg.set_info("this is external pkg");
	subPackage::MyPackage* pSubPkg = pkg.mutable_subpkg();
	pSubPkg->set_info("this is internal pkg");

	string sendData;
	pkg.SerializeToString(&sendData);

	package::MyPackage recvPkg;
	recvPkg.ParseFromString(sendData);
	subPackage::MyPackage subRecvPkg = recvPkg.subpkg();

	cout << "SEND   DATA: " << pkg.info() << " " << pSubPkg->info() << endl << endl;
	cout << "SERIAL DATA: " << sendData << endl << endl;
	cout << "RECV   DATA: " << recvPkg.info() << " " << subRecvPkg.info() << endl;
}