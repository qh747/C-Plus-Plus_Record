#include "MyMessageTest.h"

/*protobufs使用MyMessage测试函数					**/
void funcMyMessageTest()
{
	/*创建数据类									**/
	MyMessage sendMessage;

	/*初始化数据类									**/
	sendMessage.set_name(1);
	sendMessage.set_age(18);
	sendMessage.set_sex(true);
	sendMessage.set_info("hello world.");
	int phoneArray[11] = { 1,7,7,2,3,5,7,2,1,2,3 };
	for (int i = 0; i < 11; ++i)
	{
		sendMessage.add_phone(phoneArray[i]);
	}

	/*序列化数据类									**/
	string sendData;
	sendMessage.SerializeToString(&sendData);

	/*反序列化数据类								**/
	MyMessage recvMessage;
	recvMessage.ParseFromString(sendData);

	/*模拟数据传输过程的输出打印					**/
	cout << "------------------ SEND SOURCE DATA --------------------" << endl;
	cout << "name  : " << sendMessage.name() << endl;
	cout << "age   : " << sendMessage.age() << endl;
	cout << "sex   : " << sendMessage.sex() << endl;
	cout << "phone : ";
	for (int i = 0; i < sendMessage.phone_size(); ++i)
	{
		cout << sendMessage.phone(i);
	}
	cout << endl << endl;

	cout << "------------------ SEND SERIAL DATA --------------------" << endl;
	cout << sendData << endl << endl;

	cout << "------------------    DATA TRANS    --------------------" << endl;
	for (int i = 0; i < 3; ++i)
	{
		cout << "data trans..." << endl;
		Sleep(1 * 1000);
	}
	cout << endl;

	cout << "------------------ RECV SERIAL DATA --------------------" << endl;
	cout << sendData << endl;

	cout << "------------------ RECV SOURCE DATA --------------------" << endl;
	cout << "name  : " << recvMessage.name() << endl;
	cout << "age   : " << recvMessage.age() << endl;
	cout << "sex   : " << recvMessage.sex() << endl;
	cout << "phone : ";
	for (int i = 0; i < recvMessage.phone_size(); ++i)
	{
		cout << recvMessage.phone(i);
	}
	cout << endl;
}