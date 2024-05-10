#include "libRabbitMQTest.h"

/*发布者线程返回值    **/
int TOPIC_MODE_PUBLISH_THREAD_RESULT = 0;

/*第一个接收者线程返回值    **/
int TOPIC_MODE_FIRST_CONSUME_THREAD_RESULT = 0;

/*第二个接收者线程返回值    **/
int TOPIC_MODE_SECOND_CONSUME_THREAD_RESULT = 0;

void topicModeFunc()
{
	printf("************** RABBITMQ TOPIC MODE FUNC START *************\n\n");

	/*创建发布者线程    **/
	thread publishThread(topicMode_PublishThreadFunc);

	/*创建错误信息接收者线程    **/
	thread firstConsumeThread(topicMode_FirstConsumeThreadFunc);

	/*创建警告信息接收者线程    **/
	thread secondConsumeThread(topicMode_SecondConsumeThreadFunc);

	publishThread.join();
	firstConsumeThread.join();
	secondConsumeThread.join();

	printf("************** RABBITMQ TOPIC MODE FUNC END *************\n\n");

	printf("Publish Thread Result: %d\n", TOPIC_MODE_PUBLISH_THREAD_RESULT);
	printf("First Consume Thread Result: %d\n", TOPIC_MODE_FIRST_CONSUME_THREAD_RESULT);
	printf("Second Consume Thread Result: %d\n", TOPIC_MODE_SECOND_CONSUME_THREAD_RESULT);
}

int topicMode_PublishThreadFunc()
{
	/*创建与RabbitMQ Server的连接    **/
	amqp_connection_state_t pConn = amqp_new_connection();
	if (NULL == pConn)
	{
		TOPIC_MODE_PUBLISH_THREAD_RESULT = -1;
		return TOPIC_MODE_PUBLISH_THREAD_RESULT;
	}

	/*创建与RabbitMQ Server通信的socket    **/
	amqp_socket_t* pSocket = amqp_tcp_socket_new(pConn);
	if (NULL == pSocket)
	{
		TOPIC_MODE_PUBLISH_THREAD_RESULT = -1;
		return TOPIC_MODE_PUBLISH_THREAD_RESULT;
	}

	/*打开与RabbitMQ Server通信的socket    **/
	int openSocketRet = amqp_socket_open(pSocket, "192.168.0.188", 5672);
	if (AMQP_STATUS_OK != openSocketRet)
	{
		TOPIC_MODE_PUBLISH_THREAD_RESULT = -1;
		return TOPIC_MODE_PUBLISH_THREAD_RESULT;
	}

	/*登录RabbitMQ Server    **/
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");
	if (AMQP_RESPONSE_NORMAL != loginRet.reply_type)
	{
		TOPIC_MODE_PUBLISH_THREAD_RESULT = -1;
		return TOPIC_MODE_PUBLISH_THREAD_RESULT;
	}

	/*打开通信管道    **/
	int channelId = 1;
	amqp_channel_open_ok_t* openChannelRet = amqp_channel_open(pConn, channelId);

	/*声明交换机    **/
	string exchangeName = "test_topicMode_exchange";
	string exchangeType = "topic";
	amqp_exchange_declare_ok_t* pDeclareRet = amqp_exchange_declare(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes(exchangeType.c_str()), false, true, false, false, amqp_empty_table);

	/*发布消息   **/
	amqp_bytes_t messageBody;
	char messageBuf[32] = "\0";

	/*给第一个队列发布消息    **/
	strcpy(messageBuf, "first queue receive 1.");
	messageBody.bytes = messageBuf;
	messageBody.len = sizeof(messageBuf);
	int publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes("to.first.queue"), 0, 0, NULL, messageBody);
	printf("Pubilsh Send: %s\n", messageBuf);

	Sleep(1000);
	memset(&messageBody, 0, sizeof(amqp_bytes_t));
	memset(messageBuf, 0, 32);

	strcpy(messageBuf, "first queue receive 2.");
	messageBody.bytes = messageBuf;
	messageBody.len = sizeof(messageBuf);
	publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes("send.first.thread"), 0, 0, NULL, messageBody);
	printf("Pubilsh Send: %s\n", messageBuf);

	Sleep(1000);
	memset(&messageBody, 0, sizeof(amqp_bytes_t));
	memset(messageBuf, 0, 32);

	strcpy(messageBuf, "quit");
	messageBody.bytes = messageBuf;
	messageBody.len = sizeof(messageBuf);
	publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes("let.first.quit"), 0, 0, NULL, messageBody);
	printf("Pubilsh Make First Queue Exit\n");

	Sleep(1000);
	memset(&messageBody, 0, sizeof(amqp_bytes_t));
	memset(messageBuf, 0, 32);

	/*给第二个队列发布消息**/
	strcpy(messageBuf, "second queue receive 1.");
	messageBody.bytes = messageBuf;
	messageBody.len = sizeof(messageBuf);
	publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes("2.to.queue"), 0, 0, NULL, messageBody);
	printf("Pubilsh Send: %s\n", messageBuf);

	Sleep(1000);
	memset(&messageBody, 0, sizeof(amqp_bytes_t));
	memset(messageBuf, 0, 32);

	strcpy(messageBuf, "second queue receive 2.");
	messageBody.bytes = messageBuf;
	messageBody.len = sizeof(messageBuf);
	publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes("send.message.to.queue"), 0, 0, NULL, messageBody);
	printf("Pubilsh Send: %s\n", messageBuf);

	Sleep(1000);
	memset(&messageBody, 0, sizeof(amqp_bytes_t));
	memset(messageBuf, 0, 32);

	strcpy(messageBuf, "quit");
	messageBody.bytes = messageBuf;
	messageBody.len = sizeof(messageBuf);
	publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes("quit.the.second.queue"), 0, 0, NULL, messageBody);
	printf("Pubilsh Make Second Queue Exit\n");

	Sleep(1000);
	memset(&messageBody, 0, sizeof(amqp_bytes_t));
	memset(messageBuf, 0, 32);

	/*关闭通信管道    **/
	amqp_channel_close(pConn, channelId, AMQP_REPLY_SUCCESS);

	/*销毁与RabbitM去Server通信的socket    **/
	amqp_connection_close(pConn, AMQP_REPLY_SUCCESS);

	/*释放与RabbitMQ Server连接占用的内存空间    **/
	amqp_maybe_release_buffers(pConn);

	/*销毁与RabbitMQ Server的连接    **/
	amqp_destroy_connection(pConn);

	TOPIC_MODE_PUBLISH_THREAD_RESULT = 1;
	return TOPIC_MODE_PUBLISH_THREAD_RESULT;
}

int topicMode_FirstConsumeThreadFunc()
{
	/*创建与RabbitMQ Server的连接    **/
	amqp_connection_state_t pConn = amqp_new_connection();
	if (NULL == pConn)
	{
		TOPIC_MODE_FIRST_CONSUME_THREAD_RESULT = -1;
		return TOPIC_MODE_FIRST_CONSUME_THREAD_RESULT;
	}

	/*创建与RabbitMQ Server通信的socket    **/
	amqp_socket_t* pSocket = amqp_tcp_socket_new(pConn);
	if (NULL == pSocket)
	{
		TOPIC_MODE_FIRST_CONSUME_THREAD_RESULT = -1;
		return TOPIC_MODE_FIRST_CONSUME_THREAD_RESULT;
	}

	/*打开与RabbitMQ Server通信的socket    **/
	int openSocketRet = amqp_socket_open(pSocket, "192.168.0.188", 5672);
	if (AMQP_STATUS_OK != openSocketRet)
	{
		TOPIC_MODE_FIRST_CONSUME_THREAD_RESULT = -1;
		return TOPIC_MODE_FIRST_CONSUME_THREAD_RESULT;
	}

	/*登录RabbitMQ Server    **/
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");
	if (AMQP_RESPONSE_NORMAL != loginRet.reply_type)
	{
		TOPIC_MODE_FIRST_CONSUME_THREAD_RESULT = -1;
		return TOPIC_MODE_FIRST_CONSUME_THREAD_RESULT;
	}

	/*打开通信管道    **/
	int channelId = 1;
	amqp_channel_open_ok_t* openChannelRet = amqp_channel_open(pConn, channelId);

	/*声明队列    **/
	amqp_queue_declare_ok_t* pDeclareRet = amqp_queue_declare(pConn, channelId, amqp_cstring_bytes("test_topicMode_first_queue"), false, true, false, false, amqp_empty_table);

	/*绑定当前队列到交换机上    **/
	amqp_queue_bind(pConn, channelId, amqp_cstring_bytes("test_topicMode_first_queue"), amqp_cstring_bytes("test_topicMode_exchange"), amqp_cstring_bytes("*.first.*"), amqp_empty_table);

	/*声明消息消费方式为队列主动推送    **/
	amqp_basic_consume(pConn, channelId, amqp_cstring_bytes("test_topicMode_first_queue"), amqp_empty_bytes, false, true, false, amqp_empty_table);

	/*消费消息    **/
	while (true)
	{
		amqp_envelope_t envelope;
		amqp_rpc_reply_t ret = amqp_consume_message(pConn, &envelope, NULL, 0);
		if (0 == strcmp("quit", (char *)envelope.message.body.bytes))
			break;
		else
			printf("First Consume Receive: %s\n", (char *)envelope.message.body.bytes);

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

	TOPIC_MODE_FIRST_CONSUME_THREAD_RESULT = 1;
	return TOPIC_MODE_FIRST_CONSUME_THREAD_RESULT;
}

int topicMode_SecondConsumeThreadFunc()
{
	/*创建与RabbitMQ Server的连接    **/
	amqp_connection_state_t pConn = amqp_new_connection();
	if (NULL == pConn)
	{
		TOPIC_MODE_SECOND_CONSUME_THREAD_RESULT = -1;
		return TOPIC_MODE_SECOND_CONSUME_THREAD_RESULT;
	}

	/*创建与RabbitMQ Server通信的socket    **/
	amqp_socket_t* pSocket = amqp_tcp_socket_new(pConn);
	if (NULL == pSocket)
	{
		TOPIC_MODE_SECOND_CONSUME_THREAD_RESULT = -1;
		return TOPIC_MODE_SECOND_CONSUME_THREAD_RESULT;
	}

	/*打开与RabbitMQ Server通信的socket    **/
	int openSocketRet = amqp_socket_open(pSocket, "192.168.0.188", 5672);
	if (AMQP_STATUS_OK != openSocketRet)
	{
		TOPIC_MODE_SECOND_CONSUME_THREAD_RESULT = -1;
		return TOPIC_MODE_SECOND_CONSUME_THREAD_RESULT;
	}

	/*登录RabbitMQ Server    **/
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");
	if (AMQP_RESPONSE_NORMAL != loginRet.reply_type)
	{
		TOPIC_MODE_SECOND_CONSUME_THREAD_RESULT = -1;
		return TOPIC_MODE_SECOND_CONSUME_THREAD_RESULT;
	}

	/*打开通信管道    **/
	int channelId = 1;
	amqp_channel_open_ok_t* openChannelRet = amqp_channel_open(pConn, channelId);

	/*声明队列    **/
	amqp_queue_declare_ok_t* pDeclareRet = amqp_queue_declare(pConn, channelId, amqp_cstring_bytes("test_topicMode_second_queue"), false, true, false, false, amqp_empty_table);

	/*绑定当前队列到交换机上    **/
	amqp_queue_bind(pConn, channelId, amqp_cstring_bytes("test_topicMode_second_queue"), amqp_cstring_bytes("test_topicMode_exchange"), amqp_cstring_bytes("2.#"), amqp_empty_table);
	amqp_queue_bind(pConn, channelId, amqp_cstring_bytes("test_topicMode_second_queue"), amqp_cstring_bytes("test_topicMode_exchange"), amqp_cstring_bytes("*.*.*.queue"), amqp_empty_table);

	/*声明消息消费方式为队列主动推送    **/
	amqp_basic_consume(pConn, channelId, amqp_cstring_bytes("test_topicMode_second_queue"), amqp_empty_bytes, false, true, false, amqp_empty_table);

	/*消费消息    **/
	while (true)
	{
		amqp_envelope_t envelope;
		amqp_rpc_reply_t ret = amqp_consume_message(pConn, &envelope, NULL, 0);
		if (0 == strcmp("quit", (char *)envelope.message.body.bytes))
			break;
		else
			printf("Second Consume Receive: %s\n", (char *)envelope.message.body.bytes);

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

	TOPIC_MODE_SECOND_CONSUME_THREAD_RESULT = 1;
	return TOPIC_MODE_SECOND_CONSUME_THREAD_RESULT;
}