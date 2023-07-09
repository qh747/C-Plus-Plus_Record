#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "../Protobuf/Request.h"
#include "../Protobuf/Response.h"
#include "../Socket/TcpServer.h"
#include "../Socket/TcpSocket.h"
#include "../MemoryShare/MemoryShare.h"
#include "../MemoryShare/ClientMemShare.h"
#include "../OpenSSL/Encrypt.h"
#include "../OpenSSL/RsaEncrypt.h"
#include "../JsonCpp/ClientJsonCpp.h"
#include <Windows.h>

using namespace std;

/*编解码模块测试							**/
void funcThreadCodecTest();
void funcModelRequestCodecTest();
void funcModelResponseCodecTest();

/*Socket模块测试							**/
void funcThreadSocketTest();
void funcModelTcpServerTest();
void funcModelTcpClientTest();

/*共享内存模块测试							**/
void funcMemoryShareTest();
void funcModelMemoryShareWriteTest();
void funcModelMemoryShareReadTest();
void funModelClientMemoryShareTest();

/*加密模块测试								**/
void funcEncryptTest();
void funcRsaEncryptTest();

/*json读取配置模块测试						**/
void funcClientJsonConfTest();