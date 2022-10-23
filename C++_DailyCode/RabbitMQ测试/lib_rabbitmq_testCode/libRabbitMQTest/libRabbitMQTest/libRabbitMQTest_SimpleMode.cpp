#include "libRabbitMQTest.h"

/*发布者线程返回值    **/
int GLOBAL_PUBLISH_THREAD_RESULT = 0;

/*接收者线程返回值    **/
int GLOBAL_CONSUME_THREAD_RESULT = 0;


void simpleModeFunc()
{
	printf("************** RABBITMQ SIMPLE MODE FUNC START *************\n\n");

	/*创建发布者线程    **/
	thread publishThread(simpleMode_PublishThreadFunc);

	/*创建接收者线程    **/
	thread consumeThread(simpleMode_ConsumeThreadFunc);

	publishThread.join();
	consumeThread.join();

	printf("************** RABBITMQ SIMPLE MODE FUNC END *************\n\n");

	printf("Publish Thread Result: %d\n", GLOBAL_PUBLISH_THREAD_RESULT);
	printf("Consume Thread Result: %d\n", GLOBAL_CONSUME_THREAD_RESULT);
}

int simpleMode_PublishThreadFunc()
{
	/*创建一个与RabbitMQ Server的连接    **/
	amqp_connection_state_t pConn = NULL;
	pConn = amqp_new_connection();

	if (NULL == pConn)
	{
		GLOBAL_PUBLISH_THREAD_RESULT = -1;
		return GLOBAL_PUBLISH_THREAD_RESULT;
	}

	/*创建一个与RabbitMQ Server通信的socket    **/
	amqp_socket_t* pSocket = NULL;
	pSocket = amqp_tcp_socket_new(pConn);

	if (NULL == pSocket)
	{
		GLOBAL_PUBLISH_THREAD_RESULT = -1;
		return GLOBAL_PUBLISH_THREAD_RESULT;
	}

	/*打开与RabbitMQ Server通信的socket    **/
	string hostName = "192.168.0.188";
	int port = 5672;
	int openSockRet = amqp_socket_open(pSocket, hostName.c_str(), port);
	if (AMQP_STATUS_OK != openSockRet)
	{
		GLOBAL_PUBLISH_THREAD_RESULT = -1;
		return GLOBAL_PUBLISH_THREAD_RESULT;
	}

	/*登录RabbitMQ Server, 用于权限管理    **/
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");

	/*打开通信管道    **/
	amqp_channel_t channelId = 1;
	amqp_channel_open_ok_t* pCannelOpenRet = amqp_channel_open(pConn, channelId);

	/*发布消息    **/
	for (int i = 0; i < 3; ++i)
	{
		/*生成消息    **/
		char message[64] = "\0";
		sprintf(message, "%s: %d", "Data", i);

		amqp_bytes_t message_bytes;
		message_bytes.len = sizeof(message);
		message_bytes.bytes = message;

		/*发送消息    **/
		int publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(""), amqp_cstring_bytes("test_simple_queue"), 0, 0, nullptr, message_bytes);
		if (AMQP_STATUS_OK == publishRet)
			printf("Publisher Send Message : %s\n\n", message);

		Sleep(1000);
	}

	/*释放内存空间    **/
	amqp_maybe_release_buffers(pConn);

	/*关闭通信管道    **/
	amqp_rpc_reply_t closeChannelRet = amqp_channel_close(pConn, channelId, AMQP_REPLY_SUCCESS);

	/*关闭连接    **/
	amqp_rpc_reply_t closeConnectRet = amqp_connection_close(pConn, AMQP_REPLY_SUCCESS);

	/*销毁链接    **/
	int destoryRet = amqp_destroy_connection(pConn);
	if (AMQP_STATUS_OK != destoryRet)
	{
		GLOBAL_PUBLISH_THREAD_RESULT = -1;
		return GLOBAL_PUBLISH_THREAD_RESULT;
	}

	/*流程正常进行结束，返回1    **/
	GLOBAL_PUBLISH_THREAD_RESULT = 1;
	return GLOBAL_PUBLISH_THREAD_RESULT;
}

int simpleMode_ConsumeThreadFunc()
{
	/*创建一个与RabbitMQ通信的连接    **/
	amqp_connection_state_t pConn = NULL;
	pConn = amqp_new_connection();
	if (NULL == pConn)
	{
		GLOBAL_CONSUME_THREAD_RESULT = -1;
		return GLOBAL_CONSUME_THREAD_RESULT;
	}

	/*创建一个与RabbitMQ通信的socket    **/
	amqp_socket_t* pSocket = nullptr;
	pSocket = amqp_tcp_socket_new(pConn);
	if (NULL == pSocket)
	{
		GLOBAL_CONSUME_THREAD_RESULT = -1;
		return GLOBAL_CONSUME_THREAD_RESULT;
	}

	/*打开与RabbitMQ通信的连接    **/
	string hostName = "192.168.0.188";
	int port = 5672;

	int openRet = amqp_socket_open(pSocket, hostName.c_str(), port);
	if (AMQP_STATUS_OK != openRet)
	{
		GLOBAL_CONSUME_THREAD_RESULT = -1;
		return GLOBAL_CONSUME_THREAD_RESULT;
	}

	//登录RabbitMQ
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");
	if (AMQP_RESPONSE_NORMAL != loginRet.reply_type)
	{
		GLOBAL_CONSUME_THREAD_RESULT = -1;
		return GLOBAL_CONSUME_THREAD_RESULT;
	}

	/*打开与RabbitMQ通信的管道    **/
	amqp_channel_t channelId = 1;
	amqp_channel_open_ok_t* openChannelRet = amqp_channel_open(pConn, channelId);

	/*消费消息    **/
	int msgCount = 0;

	amqp_basic_consume_ok_t *msg = amqp_basic_consume(pConn, channelId, amqp_cstring_bytes("test_simple_queue"), amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
	
	while (1)
	{
		/*指定等待时间    **/
		amqp_envelope_t* pEnvelope = new amqp_envelope_t();
		timeval timeout = timeval{ 2, 0 };

		amqp_consume_message(pConn, pEnvelope, &timeout, 0);
		++msgCount;

		if (0 == pEnvelope->message.body.bytes)
			continue;

		printf("Consumer Receive Message : %s\n\n", (char *)pEnvelope->message.body.bytes);

		amqp_destroy_envelope(pEnvelope);

		if (msgCount >= 3)
			break;
	}

	/*释放内存空间    **/
	amqp_maybe_release_buffers(pConn);

	/*关闭通信管道    **/
	amqp_rpc_reply_t closeChannelRet = amqp_channel_close(pConn, channelId, AMQP_REPLY_SUCCESS);

	/*关闭连接    **/
	amqp_rpc_reply_t closeConnectRet = amqp_connection_close(pConn, AMQP_REPLY_SUCCESS);

	/*销毁链接    **/
	int destoryRet = amqp_destroy_connection(pConn);
	if (AMQP_STATUS_OK != destoryRet)
	{
		GLOBAL_CONSUME_THREAD_RESULT = -1;
		return GLOBAL_CONSUME_THREAD_RESULT;
	}

	/*流程正常进行结束，返回1    **/
	GLOBAL_CONSUME_THREAD_RESULT = 1;
	return GLOBAL_CONSUME_THREAD_RESULT;
}

