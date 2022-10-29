#include "libRabbitMQTest.h"

/*发布者线程返回值    **/
int PUBANDSUB_MODE_PUBLISH_THREAD_RESULT = 0;

/*接收者线程返回值    **/
int PUBANDSUB_MODE_CONSUME_THREAD_RESULT = 0;

/*第二个接收者线程返回值    **/
int PUBANDSUB_MODE_SECOND_CONSUME_THREAD_RESULT = 0;

void pubAndSubModeFunc()
{
	printf("************** RABBITMQ PUBLISH AND SUBSCRBE MODE FUNC START *************\n\n");

	/*创建发布者线程    **/
	thread publishThread(pubAndSubMode_PublishThreadFunc);

	/*创建接收者线程    **/
	thread consumeThread(pubAndSubMode_ConsumeThreadFunc);

	/*创建第二个接收者线程    **/
	thread secondConsumeThread(pubAndSubMode_SecondConsumeThreadFunc);

	publishThread.join();
	consumeThread.join();
	secondConsumeThread.join();

	printf("\n************** RABBITMQ PUBLISH AND SUBSCRBE MODE FUNC END *************\n\n");

	printf("Publish Thread Result: %d\n", PUBANDSUB_MODE_PUBLISH_THREAD_RESULT);
	printf("Consume Thread Result: %d\n", PUBANDSUB_MODE_CONSUME_THREAD_RESULT);
	printf("Second Consume Thread Result: %d\n", PUBANDSUB_MODE_SECOND_CONSUME_THREAD_RESULT);
}

int pubAndSubMode_PublishThreadFunc()
{
	/*创建与RabbitMQ Server的连接    **/
	amqp_connection_state_t pConn = amqp_new_connection();
	if (NULL == pConn)
	{
		PUBANDSUB_MODE_PUBLISH_THREAD_RESULT = -1;
		return PUBANDSUB_MODE_PUBLISH_THREAD_RESULT;
	}

	/*创建与RabbitMQ Server通信的socket    **/
	amqp_socket_t* pSocket = amqp_tcp_socket_new(pConn);
	if (NULL == pSocket)
	{
		PUBANDSUB_MODE_PUBLISH_THREAD_RESULT = -1;
		return PUBANDSUB_MODE_PUBLISH_THREAD_RESULT;
	}

	/*打开与RabbitMQ Server通信的socket    **/
	int openSocketRet = amqp_socket_open(pSocket, "192.168.0.188", 5672);
	if (AMQP_STATUS_OK != openSocketRet)
	{
		PUBANDSUB_MODE_PUBLISH_THREAD_RESULT = -1;
		return PUBANDSUB_MODE_PUBLISH_THREAD_RESULT;
	}

	/*登录RabbitMQ Server    **/
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");
	if (AMQP_RESPONSE_NORMAL != loginRet.reply_type)
	{
		PUBANDSUB_MODE_PUBLISH_THREAD_RESULT = -1;
		return PUBANDSUB_MODE_PUBLISH_THREAD_RESULT;
	}

	/*打开通信管道    **/
	int channelId = 1;
	amqp_channel_open_ok_t* openChannelRet = amqp_channel_open(pConn, channelId);

	/*声明交换机    **/
	string exchangeName = "test_pubAndSubMode_exchange";
	string exchangeType = "fanout";
	amqp_exchange_declare_ok_t* pDeclareRet = amqp_exchange_declare(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes(exchangeType.c_str()), false, true, false, false, amqp_empty_table);

	/*发布消息   **/
	stringstream strBuf;

	for (int i = 0; i <= 10; ++i)
	{
		amqp_bytes_t messageBody;
		
		if (10 != i)
		{
			/*发布普通消息    **/
			strBuf << "DATA: " << i;
			char messageBuf[16] = "\0";
			strcpy(messageBuf, strBuf.str().c_str());

			messageBody.bytes = messageBuf;
			messageBody.len = sizeof(messageBuf);

			int publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes(""), 0, 0, NULL, messageBody);

			printf("\nThread: %d Send: %s\n", this_thread::get_id(), messageBuf);
		}
		else
		{
			/*发布一条标识消费者线程结束的消息    **/
			char messageBuf[16] = "quit";

			messageBody.bytes = messageBuf;
			messageBody.len = sizeof(messageBuf);

			int publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(exchangeName.c_str()), amqp_cstring_bytes(""), 0, 0, NULL, messageBody);
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

	PUBANDSUB_MODE_PUBLISH_THREAD_RESULT = 1;
	return PUBANDSUB_MODE_PUBLISH_THREAD_RESULT;
}

int pubAndSubMode_ConsumeThreadFunc()
{
	/*创建与RabbitMQ Server的连接    **/
	amqp_connection_state_t pConn = amqp_new_connection();
	if (NULL == pConn)
	{
		PUBANDSUB_MODE_CONSUME_THREAD_RESULT = -1;
		return PUBANDSUB_MODE_CONSUME_THREAD_RESULT;
	}

	/*创建与RabbitMQ Server通信的socket    **/
	amqp_socket_t* pSocket = amqp_tcp_socket_new(pConn);
	if (NULL == pSocket)
	{
		PUBANDSUB_MODE_CONSUME_THREAD_RESULT = -1;
		return PUBANDSUB_MODE_CONSUME_THREAD_RESULT;
	}

	/*打开与RabbitMQ Server通信的socket    **/
	int openSocketRet = amqp_socket_open(pSocket, "192.168.0.188", 5672);
	if (AMQP_STATUS_OK != openSocketRet)
	{
		PUBANDSUB_MODE_CONSUME_THREAD_RESULT = -1;
		return PUBANDSUB_MODE_CONSUME_THREAD_RESULT;
	}

	/*登录RabbitMQ Server    **/
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");
	if (AMQP_RESPONSE_NORMAL != loginRet.reply_type)
	{
		PUBANDSUB_MODE_CONSUME_THREAD_RESULT = -1;
		return PUBANDSUB_MODE_CONSUME_THREAD_RESULT;
	}

	/*打开通信管道    **/
	int channelId = 1;
	amqp_channel_open_ok_t* openChannelRet = amqp_channel_open(pConn, channelId);

	/*声明队列    **/
	amqp_queue_declare_ok_t* pDeclareRet = amqp_queue_declare(pConn, channelId, amqp_cstring_bytes("test_pubAndSubMode_queue"), false, true, false, false, amqp_empty_table);

	/*绑定当前队列到交换机上    **/
	amqp_queue_bind(pConn, channelId, amqp_cstring_bytes("test_pubAndSubMode_queue"), amqp_cstring_bytes("test_pubAndSubMode_exchange"), amqp_cstring_bytes(""), amqp_empty_table);

	/*声明消息消费方式为队列主动推送    **/
	amqp_basic_consume(pConn, channelId, amqp_cstring_bytes("test_pubAndSubMode_queue"), amqp_empty_bytes, false, true, false, amqp_empty_table);

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

	PUBANDSUB_MODE_CONSUME_THREAD_RESULT = 1;
	return PUBANDSUB_MODE_CONSUME_THREAD_RESULT;
}

int pubAndSubMode_SecondConsumeThreadFunc()
{
	/*创建与RabbitMQ Server的连接    **/
	amqp_connection_state_t pConn = amqp_new_connection();
	if (NULL == pConn)
	{
		PUBANDSUB_MODE_SECOND_CONSUME_THREAD_RESULT = -1;
		return PUBANDSUB_MODE_SECOND_CONSUME_THREAD_RESULT;
	}

	/*创建与RabbitMQ Server通信的socket    **/
	amqp_socket_t* pSocket = amqp_tcp_socket_new(pConn);
	if (NULL == pSocket)
	{
		PUBANDSUB_MODE_SECOND_CONSUME_THREAD_RESULT = -1;
		return PUBANDSUB_MODE_SECOND_CONSUME_THREAD_RESULT;
	}

	/*打开与RabbitMQ Server通信的socket    **/
	int openSocketRet = amqp_socket_open(pSocket, "192.168.0.188", 5672);
	if (AMQP_STATUS_OK != openSocketRet)
	{
		PUBANDSUB_MODE_SECOND_CONSUME_THREAD_RESULT = -1;
		return PUBANDSUB_MODE_SECOND_CONSUME_THREAD_RESULT;
	}

	/*登录RabbitMQ Server    **/
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");
	if (AMQP_RESPONSE_NORMAL != loginRet.reply_type)
	{
		PUBANDSUB_MODE_SECOND_CONSUME_THREAD_RESULT = -1;
		return PUBANDSUB_MODE_SECOND_CONSUME_THREAD_RESULT;
	}

	/*打开通信管道    **/
	int channelId = 1;
	amqp_channel_open_ok_t* openChannelRet = amqp_channel_open(pConn, channelId);

	/*声明队列    **/
	amqp_queue_declare_ok_t* pDeclareRet = amqp_queue_declare(pConn, channelId, amqp_cstring_bytes("test_pubAndSubMode_second_queue"), false, true, false, false, amqp_empty_table);

	/*绑定当前队列到交换机上    **/
	amqp_queue_bind(pConn, channelId, amqp_cstring_bytes("test_pubAndSubMode_second_queue"), amqp_cstring_bytes("test_pubAndSubMode_exchange"), amqp_cstring_bytes(""), amqp_empty_table);

	/*声明消息消费方式为队列主动推送    **/
	amqp_basic_consume(pConn, channelId, amqp_cstring_bytes("test_pubAndSubMode_second_queue"), amqp_empty_bytes, false, true, false, amqp_empty_table);

	/*消费消息    **/
	while (true)
	{
		amqp_envelope_t envelope;
		amqp_rpc_reply_t ret = amqp_consume_message(pConn, &envelope, NULL, 0);
		if (0 == strcmp("quit", (char *)envelope.message.body.bytes))
			break;
		else
			printf("Thread: %d Second Receive: %s\n", this_thread::get_id(), (char *)envelope.message.body.bytes);

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

	PUBANDSUB_MODE_SECOND_CONSUME_THREAD_RESULT = 1;
	return PUBANDSUB_MODE_SECOND_CONSUME_THREAD_RESULT;
}