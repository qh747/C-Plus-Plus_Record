#include "libRabbitMQTest.h"

/*发布者线程返回值    **/
int ROUTE_MODE_PUBLISH_THREAD_RESULT = 0;

/*错误信息接收者线程返回值    **/
int ROUTE_MODE_ERROR_CONSUME_THREAD_RESULT = 0;

/*警告信息线程返回值    **/
int ROUTE_MODE_WARN_CONSUME_THREAD_RESULT = 0;

/*普通信息线程返回值    **/
int ROUTE_MODE_INFO_CONSUME_THREAD_RESULT = 0;


void routeModeFunc()
{
	printf("************** RABBITMQ ROUTE MODE FUNC START *************\n\n");

	/*创建发布者线程    **/
	thread publishThread(routeMode_PublishThreadFunc);

	/*创建错误信息接收者线程    **/
	thread errorConsumeThread(routeMode_ErrorConsumeThreadFunc);

	/*创建警告信息接收者线程    **/
	thread warnConsumeThread(routeMode_WarnConsumeThreadFunc);

	/*创建普通信息接收者线程    **/
	thread infoConsumeThread(routeMode_InfoConsumeThreadFunc);

	publishThread.join();
	errorConsumeThread.join();
	warnConsumeThread.join();
	infoConsumeThread.join();

	printf("************** RABBITMQ ROUTE MODE FUNC END *************\n\n");

	printf("Publish Thread Result: %d\n", ROUTE_MODE_PUBLISH_THREAD_RESULT);
	printf("Error Consume Thread Result: %d\n", ROUTE_MODE_ERROR_CONSUME_THREAD_RESULT);
	printf("Warn Consume Thread Result: %d\n", ROUTE_MODE_WARN_CONSUME_THREAD_RESULT);
	printf("Info Consume Thread Result: %d\n", ROUTE_MODE_INFO_CONSUME_THREAD_RESULT);
}

int routeMode_PublishThreadFunc()
{
	/*创建与RabbitMQ Server的连接    **/
	amqp_connection_state_t pConn = amqp_new_connection();
	if (NULL == pConn)
	{
		ROUTE_MODE_PUBLISH_THREAD_RESULT = -1;
		return ROUTE_MODE_PUBLISH_THREAD_RESULT;
	}

	/*创建与RabbitMQ Server通信的socket    **/
	amqp_socket_t* pSocket = amqp_tcp_socket_new(pConn);
	if (NULL == pSocket)
	{
		ROUTE_MODE_PUBLISH_THREAD_RESULT = -1;
		return ROUTE_MODE_PUBLISH_THREAD_RESULT;
	}

	/*打开与RabbitMQ Server通信的socket    **/
	int openSocketRet = amqp_socket_open(pSocket, "192.168.0.188", 5672);
	if (AMQP_STATUS_OK != openSocketRet)
	{
		ROUTE_MODE_PUBLISH_THREAD_RESULT = -1;
		return ROUTE_MODE_PUBLISH_THREAD_RESULT;
	}

	/*登录RabbitMQ Server    **/
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");
	if (AMQP_RESPONSE_NORMAL != loginRet.reply_type)
	{
		ROUTE_MODE_PUBLISH_THREAD_RESULT = -1;
		return ROUTE_MODE_PUBLISH_THREAD_RESULT;
	}

	/*打开通信管道    **/
	int channelId = 1;
	amqp_channel_open_ok_t* openChannelRet = amqp_channel_open(pConn, channelId);

	/*声明交换机    **/
	string exchangeName = "test_RouteMode_exchange";
	string exchangeType = "direct";
	amqp_exchange_declare_ok_t* pDeclareRet = amqp_exchange_declare(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes(exchangeType.c_str()), false, true, false, false, amqp_empty_table);

	/*发布消息   **/
	stringstream strBuf;

	for (int i = 0; i <= 10; ++i)
	{
		amqp_bytes_t messageBody;

		if(10 == i)
		{
			/*发布一条标识消费者线程结束的消息    **/
			char messageBuf[16] = "quit";

			messageBody.bytes = messageBuf;
			messageBody.len = sizeof(messageBuf);

			int publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes("Error"), 0, 0, NULL, messageBody);
			publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes("Warn"), 0, 0, NULL, messageBody);
			publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes("Info"), 0, 0, NULL, messageBody);
		}
		else if (0 == i % 2)
		{
			/*发布错误消息    **/
			strBuf << "DATA: Error " << i;
			char messageBuf[16] = "\0";
			strcpy(messageBuf, strBuf.str().c_str());

			messageBody.bytes = messageBuf;
			messageBody.len = sizeof(messageBuf);

			int publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes("Error"), 0, 0, NULL, messageBody);

			printf("\nThread: %d Send: %s\n", this_thread::get_id(), messageBuf);
		}
		else if (0 == i % 3)
		{
			/*发布警告消息    **/
			strBuf << "DATA: Warn " << i;
			char messageBuf[16] = "\0";
			strcpy(messageBuf, strBuf.str().c_str());

			messageBody.bytes = messageBuf;
			messageBody.len = sizeof(messageBuf);

			int publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes("Warn"), 0, 0, NULL, messageBody);

			printf("\nThread: %d Send: %s\n", this_thread::get_id(), messageBuf);
		}
		else
		{
			/*发布普通消息    **/
			strBuf << "DATA: Info " << i;
			char messageBuf[16] = "\0";
			strcpy(messageBuf, strBuf.str().c_str());

			messageBody.bytes = messageBuf;
			messageBody.len = sizeof(messageBuf);

			int publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes("Info"), 0, 0, NULL, messageBody);

			printf("\nThread: %d Send: %s\n", this_thread::get_id(), messageBuf);
		}

		strBuf.str("");
		Sleep(1000);
	}

	/*关闭通信管道    **/
	amqp_channel_close(pConn, channelId, AMQP_REPLY_SUCCESS);

	/*销毁与RabbitM去Server通信的socket    **/
	amqp_connection_close(pConn, AMQP_REPLY_SUCCESS);

	/*释放与RabbitMQ Server连接占用的内存空间    **/
	amqp_maybe_release_buffers(pConn);

	/*销毁与RabbitMQ Server的连接    **/
	amqp_destroy_connection(pConn);

	ROUTE_MODE_PUBLISH_THREAD_RESULT = 1;
	return ROUTE_MODE_PUBLISH_THREAD_RESULT;
}

int routeMode_ErrorConsumeThreadFunc()
{
	/*创建与RabbitMQ Server的连接    **/
	amqp_connection_state_t pConn = amqp_new_connection();
	if (NULL == pConn)
	{
		ROUTE_MODE_ERROR_CONSUME_THREAD_RESULT = -1;
		return ROUTE_MODE_ERROR_CONSUME_THREAD_RESULT;
	}

	/*创建与RabbitMQ Server通信的socket    **/
	amqp_socket_t* pSocket = amqp_tcp_socket_new(pConn);
	if (NULL == pSocket)
	{
		ROUTE_MODE_ERROR_CONSUME_THREAD_RESULT = -1;
		return ROUTE_MODE_ERROR_CONSUME_THREAD_RESULT;
	}

	/*打开与RabbitMQ Server通信的socket    **/
	int openSocketRet = amqp_socket_open(pSocket, "192.168.0.188", 5672);
	if (AMQP_STATUS_OK != openSocketRet)
	{
		ROUTE_MODE_ERROR_CONSUME_THREAD_RESULT = -1;
		return ROUTE_MODE_ERROR_CONSUME_THREAD_RESULT;
	}

	/*登录RabbitMQ Server    **/
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");
	if (AMQP_RESPONSE_NORMAL != loginRet.reply_type)
	{
		ROUTE_MODE_ERROR_CONSUME_THREAD_RESULT = -1;
		return ROUTE_MODE_ERROR_CONSUME_THREAD_RESULT;
	}

	/*打开通信管道    **/
	int channelId = 1;
	amqp_channel_open_ok_t* openChannelRet = amqp_channel_open(pConn, channelId);

	/*声明队列    **/
	amqp_queue_declare_ok_t* pDeclareRet = amqp_queue_declare(pConn, channelId, amqp_cstring_bytes("test_routeMode_error_queue"), false, true, false, false, amqp_empty_table);

	/*绑定当前队列到交换机上    **/
	amqp_queue_bind(pConn, channelId, amqp_cstring_bytes("test_routeMode_error_queue"), amqp_cstring_bytes("test_RouteMode_exchange"), amqp_cstring_bytes("Error"), amqp_empty_table);

	/*声明消息消费方式为队列主动推送    **/
	amqp_basic_consume(pConn, channelId, amqp_cstring_bytes("test_routeMode_error_queue"), amqp_empty_bytes, false, true, false, amqp_empty_table);

	/*消费消息    **/
	while (true)
	{
		amqp_envelope_t envelope;
		amqp_rpc_reply_t ret = amqp_consume_message(pConn, &envelope, NULL, 0);
		if (0 == strcmp("quit", (char *)envelope.message.body.bytes))
			break;
		else
			printf("Thread: %d Receive: %s\n", this_thread::get_id(), (char *)envelope.message.body.bytes);

		amqp_destroy_envelope(&envelope);
		Sleep(1000);
	}

	/*关闭通信管道    **/
	amqp_channel_close(pConn, channelId, AMQP_REPLY_SUCCESS);

	/*销毁与RabbitM去Server通信的socket    **/
	amqp_connection_close(pConn, AMQP_REPLY_SUCCESS);

	/*释放与RabbitMQ Server连接占用的内存空间    **/
	amqp_maybe_release_buffers(pConn);

	/*销毁与RabbitMQ Server的连接    **/
	amqp_destroy_connection(pConn);

	ROUTE_MODE_ERROR_CONSUME_THREAD_RESULT = 1;
	return ROUTE_MODE_ERROR_CONSUME_THREAD_RESULT;
}

int routeMode_WarnConsumeThreadFunc()
{
	/*创建与RabbitMQ Server的连接    **/
	amqp_connection_state_t pConn = amqp_new_connection();
	if (NULL == pConn)
	{
		ROUTE_MODE_WARN_CONSUME_THREAD_RESULT = -1;
		return ROUTE_MODE_WARN_CONSUME_THREAD_RESULT;
	}

	/*创建与RabbitMQ Server通信的socket    **/
	amqp_socket_t* pSocket = amqp_tcp_socket_new(pConn);
	if (NULL == pSocket)
	{
		ROUTE_MODE_WARN_CONSUME_THREAD_RESULT = -1;
		return ROUTE_MODE_WARN_CONSUME_THREAD_RESULT;
	}

	/*打开与RabbitMQ Server通信的socket    **/
	int openSocketRet = amqp_socket_open(pSocket, "192.168.0.188", 5672);
	if (AMQP_STATUS_OK != openSocketRet)
	{
		ROUTE_MODE_WARN_CONSUME_THREAD_RESULT = -1;
		return ROUTE_MODE_WARN_CONSUME_THREAD_RESULT;
	}

	/*登录RabbitMQ Server    **/
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");
	if (AMQP_RESPONSE_NORMAL != loginRet.reply_type)
	{
		ROUTE_MODE_WARN_CONSUME_THREAD_RESULT = -1;
		return ROUTE_MODE_WARN_CONSUME_THREAD_RESULT;
	}

	/*打开通信管道    **/
	int channelId = 1;
	amqp_channel_open_ok_t* openChannelRet = amqp_channel_open(pConn, channelId);

	/*声明队列    **/
	amqp_queue_declare_ok_t* pDeclareRet = amqp_queue_declare(pConn, channelId, amqp_cstring_bytes("test_routeMode_warn_queue"), false, true, false, false, amqp_empty_table);

	/*绑定当前队列到交换机上    **/
	amqp_queue_bind(pConn, channelId, amqp_cstring_bytes("test_routeMode_warn_queue"), amqp_cstring_bytes("test_RouteMode_exchange"), amqp_cstring_bytes("Warn"), amqp_empty_table);

	/*声明消息消费方式为队列主动推送    **/
	amqp_basic_consume(pConn, channelId, amqp_cstring_bytes("test_routeMode_warn_queue"), amqp_empty_bytes, false, true, false, amqp_empty_table);

	/*消费消息    **/
	while (true)
	{
		amqp_envelope_t envelope;
		amqp_rpc_reply_t ret = amqp_consume_message(pConn, &envelope, NULL, 0);
		if (0 == strcmp("quit", (char *)envelope.message.body.bytes))
			break;
		else
			printf("Thread: %d Receive: %s\n", this_thread::get_id(), (char *)envelope.message.body.bytes);

		amqp_destroy_envelope(&envelope);
		Sleep(1000);
	}

	/*关闭通信管道    **/
	amqp_channel_close(pConn, channelId, AMQP_REPLY_SUCCESS);

	/*销毁与RabbitM去Server通信的socket    **/
	amqp_connection_close(pConn, AMQP_REPLY_SUCCESS);

	/*释放与RabbitMQ Server连接占用的内存空间    **/
	amqp_maybe_release_buffers(pConn);

	/*销毁与RabbitMQ Server的连接    **/
	amqp_destroy_connection(pConn);

	ROUTE_MODE_WARN_CONSUME_THREAD_RESULT = 1;
	return ROUTE_MODE_WARN_CONSUME_THREAD_RESULT;
}


int routeMode_InfoConsumeThreadFunc()
{
	/*创建与RabbitMQ Server的连接    **/
	amqp_connection_state_t pConn = amqp_new_connection();
	if (NULL == pConn)
	{
		ROUTE_MODE_INFO_CONSUME_THREAD_RESULT = -1;
		return ROUTE_MODE_INFO_CONSUME_THREAD_RESULT;
	}

	/*创建与RabbitMQ Server通信的socket    **/
	amqp_socket_t* pSocket = amqp_tcp_socket_new(pConn);
	if (NULL == pSocket)
	{
		ROUTE_MODE_INFO_CONSUME_THREAD_RESULT = -1;
		return ROUTE_MODE_INFO_CONSUME_THREAD_RESULT;
	}

	/*打开与RabbitMQ Server通信的socket    **/
	int openSocketRet = amqp_socket_open(pSocket, "192.168.0.188", 5672);
	if (AMQP_STATUS_OK != openSocketRet)
	{
		ROUTE_MODE_INFO_CONSUME_THREAD_RESULT = -1;
		return ROUTE_MODE_INFO_CONSUME_THREAD_RESULT;
	}

	/*登录RabbitMQ Server    **/
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");
	if (AMQP_RESPONSE_NORMAL != loginRet.reply_type)
	{
		ROUTE_MODE_INFO_CONSUME_THREAD_RESULT = -1;
		return ROUTE_MODE_INFO_CONSUME_THREAD_RESULT;
	}

	/*打开通信管道    **/
	int channelId = 1;
	amqp_channel_open_ok_t* openChannelRet = amqp_channel_open(pConn, channelId);

	/*声明队列    **/
	amqp_queue_declare_ok_t* pDeclareRet = amqp_queue_declare(pConn, channelId, amqp_cstring_bytes("test_routeMode_info_queue"), false, true, false, false, amqp_empty_table);

	/*绑定当前队列到交换机上    **/
	amqp_queue_bind(pConn, channelId, amqp_cstring_bytes("test_routeMode_info_queue"), amqp_cstring_bytes("test_RouteMode_exchange"), amqp_cstring_bytes("Info"), amqp_empty_table);

	/*声明消息消费方式为队列主动推送    **/
	amqp_basic_consume(pConn, channelId, amqp_cstring_bytes("test_routeMode_info_queue"), amqp_empty_bytes, false, true, false, amqp_empty_table);

	/*消费消息    **/
	while (true)
	{
		amqp_envelope_t envelope;
		amqp_rpc_reply_t ret = amqp_consume_message(pConn, &envelope, NULL, 0);
		if (0 == strcmp("quit", (char *)envelope.message.body.bytes))
			break;
		else
			printf("Thread: %d Receive: %s\n", this_thread::get_id(), (char *)envelope.message.body.bytes);

		amqp_destroy_envelope(&envelope);
		Sleep(1000);
	}

	/*关闭通信管道    **/
	amqp_channel_close(pConn, channelId, AMQP_REPLY_SUCCESS);

	/*销毁与RabbitM去Server通信的socket    **/
	amqp_connection_close(pConn, AMQP_REPLY_SUCCESS);

	/*释放与RabbitMQ Server连接占用的内存空间    **/
	amqp_maybe_release_buffers(pConn);

	/*销毁与RabbitMQ Server的连接    **/
	amqp_destroy_connection(pConn);

	ROUTE_MODE_INFO_CONSUME_THREAD_RESULT = 1;
	return ROUTE_MODE_INFO_CONSUME_THREAD_RESULT;
}