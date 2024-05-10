#include "MyEnumMsgTest.h"

/*protobuf π”√MyEnumMsg≤‚ ‘∫Ø ˝					**/
void funcMyEnumMsgTest()
{
	MyEnumMsg enumMsg;

	enumMsg.set_enumval(MyEnum::ZERO);
	enumMsg.set_enumstr("ZERO");

	string sendData;
	enumMsg.SerializeToString(&sendData);

	MyEnumMsg recvEnumMsg;
	recvEnumMsg.ParseFromString(sendData);

	cout << "SEND   DATA: " << enumMsg.enumval() << " " << enumMsg.enumstr() << endl << endl;
	cout << "SERIAL DATA: " << sendData << endl << endl;
	cout << "RECV   DATA: " << recvEnumMsg.enumval() << " " << recvEnumMsg.enumstr() << endl;
}