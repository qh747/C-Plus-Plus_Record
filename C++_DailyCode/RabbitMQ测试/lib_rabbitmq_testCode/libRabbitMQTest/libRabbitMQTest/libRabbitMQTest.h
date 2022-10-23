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
#include "amqp.h"
#include "amqp_tcp_socket.h"

using namespace std;

/*简单模式    **/
void simpleModeFunc();

int simpleMode_PublishThreadFunc();
int simpleMode_ConsumeThreadFunc();

/*工作队列模式    **/
void workQueueModeFunc();

int workQueueMode_PublishThreadFunc();
int workQueueMode_ConsumeThreadFunc();

/*发布/订阅模式    **/
void pubAndSubModeFunc();

int pubAndSubMode_PublishThreadFunc();
int pubAndSubMode_ConsumeThreadFunc();
int pubAndSubMode_SecondConsumeThreadFunc();