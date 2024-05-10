#include "MyImportInfoTest.h"

/*protobufÊ¹ÓÃMyImportInfo²âÊÔº¯Êý					**/
void funcMyImportInfoTest()
{
	MyDetailInfo detailInfo;
	
	detailInfo.set_describe("this is import info");
	MyInfo* pInfo = detailInfo.mutable_info();
	pInfo->set_name("info content");
	pInfo->set_age(0);

	string sendData;
	detailInfo.SerializeToString(&sendData);

	MyDetailInfo recvDetailInfo;
	recvDetailInfo.ParseFromString(sendData);
	MyInfo recvInfo = recvDetailInfo.info();

	cout << "SEND   DATA: " << detailInfo.describe() << " " << pInfo->name() << " " << pInfo->age() << endl << endl;
	cout << "SERIAL DATA: " << sendData << endl << endl;
	cout << "RECV   DATA: " << recvDetailInfo.describe() << " " << recvInfo.name() << " " << recvInfo.age() << endl;
}