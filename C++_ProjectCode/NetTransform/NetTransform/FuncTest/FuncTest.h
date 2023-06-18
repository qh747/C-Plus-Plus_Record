#pragma once
#include <iostream>
#include "../Protobuf/Request.h"
#include "../Protobuf/Response.h"
#include "../Socket/TcpServer.h"
#include "../Socket/TcpSocket.h"
#include <Windows.h>
#include <cstdio>
using namespace std;

/*Request_CodecÄ£¿é²âÊÔ						**/
void funcModelRequestCodecTest();

/*Response_CodecÄ£¿é²âÊÔ					**/
void funcModelResponseCodecTest();

/*SocketÄ£¿é²âÊÔ							**/
void funcThreadSocketTest();
void funcModelTcpServerTest();
void funcModelTcpClientTest();