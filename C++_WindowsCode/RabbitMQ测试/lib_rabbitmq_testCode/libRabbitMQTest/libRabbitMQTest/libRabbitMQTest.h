#pragma once
#pragma warning(disable: 4996)
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <sstream>
#include <assert.h>
#include "amqp.h"
#include "amqp_tcp_socket.h"
using namespace std;

// rabbitmq server IP地址
namespace RabbitmqServer
{
	const static char* sServerIpAddr = "192.168.3.16";
	const static int   iServerPort = 5672;
};


/*简单模式    **/
void simpleModeFunc();					
int  simpleMode_PublishThreadFunc();	
int  simpleMode_ConsumeThreadFunc();

/*工作队列模式    **/
void workQueueModeFunc();
int  workQueueMode_PublishThreadFunc();
int  workQueueMode_ConsumeThreadFunc();

/*发布/订阅模式    **/
void pubAndSubModeFunc();
int  pubAndSubMode_PublishThreadFunc();
int  pubAndSubMode_ConsumeThreadFunc(const string& queueName);

/*路由模式    **/
void routeModeFunc();
int  routeMode_PublishThreadFunc();
int  routeMode_ErrorConsumeThreadFunc();
int  routeMode_WarnConsumeThreadFunc();
int  routeMode_InfoConsumeThreadFunc();

/*主题模式    **/
void topicModeFunc();
int  topicMode_PublishThreadFunc();
int  topicMode_FirstConsumeThreadFunc();
int  topicMode_SecondConsumeThreadFunc();

/*RPC模式    **/
void rpcModeFunc();
int  rpcMode_ClientThreadFunc();
int  rpcMode_serverThreadFunc();
