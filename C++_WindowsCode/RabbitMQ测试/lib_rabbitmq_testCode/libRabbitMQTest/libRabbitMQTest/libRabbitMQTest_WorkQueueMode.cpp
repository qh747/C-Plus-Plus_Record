#include "libRabbitMQTest.h"

/*发布者线程返回值    **/
int WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT = 0;

/*接收者线程返回值    **/
int WORK_QUEUE_MODE_CONSUME_THREAD_RESULT = 0;

/*接收者线程返回值锁    **/
mutex WORK_QUEUE_MODE_CONSUME_THREAD_RESULT_lock;

void workQueueModeFunc()
{
	printf("************** RABBITMQ WORK QUEUE MODE FUNC START *************\n\n");

	/*创建发布者线程    **/
	thread publishThread(workQueueMode_PublishThreadFunc);

	/*先让消息全部存储到队列中在进行消费    **/
	Sleep(5 * 1000);

	/*创建第一个接收者线程    **/
	thread firstConsumeThread(workQueueMode_ConsumeThreadFunc);

	/*创建第二个接收者线程, 通过两个接收线程完成公平分发的功能    **/
	thread secondConsumeThread(workQueueMode_ConsumeThreadFunc);

	publishThread.join();
	firstConsumeThread.join();
	secondConsumeThread.join();

	printf("************** RABBITMQ WORK QUEUE MODE FUNC END *************\n\n");

	printf("Publish Thread Result: %d\n", WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT);

	WORK_QUEUE_MODE_CONSUME_THREAD_RESULT_lock.lock();
	printf("Consume Thread Result: %d\n", WORK_QUEUE_MODE_CONSUME_THREAD_RESULT);
	WORK_QUEUE_MODE_CONSUME_THREAD_RESULT_lock.unlock();
}

int workQueueMode_PublishThreadFunc()
{
	/*创建与RabbitMQ Server的连接    **/
	amqp_connection_state_t pConn = amqp_new_connection();
	if (NULL == pConn)
	{
		WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT = -1;
		return WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT;
	}

	/*创建与RabbitMQ Server通信的socket    **/
	amqp_socket_t* pSocket = amqp_tcp_socket_new(pConn);
	if(NULL == pSocket)
	{
		WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT = -1;
		return WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT;
	}

	/*打开与RabbitMQ Server通信的socket    **/
	string hostName = RabbitmqServer::sServerIpAddr;
	int port = RabbitmqServer::iServerPort;
	int openSocketRet = amqp_socket_open(pSocket, hostName.c_str(), port);
	if (AMQP_STATUS_OK != openSocketRet)
	{
		WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT = -1;
		return WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT;
	}

	/*登录RabbitMQ Server    **/
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");
	if (AMQP_RESPONSE_NORMAL != loginRet.reply_type)
	{
		WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT = -1;
		return WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT;
	}

	/*打开通信管道    **/
	int channelId = 1;
	amqp_channel_open_ok_t* openChannelRet = amqp_channel_open(pConn, channelId);

	/*发布消息   **/
	stringstream strBuf;

	for (int i = 0; i < 10; ++i)
	{
		strBuf << "DATA: " << i;
		char messageBuf[16] = "\0";
		strcpy(messageBuf, strBuf.str().c_str());

		amqp_bytes_t messageBody;
		messageBody.bytes = messageBuf;
		messageBody.len = sizeof(messageBuf);

		int publishRet = amqp_basic_publish(pConn, channelId, amqp_cstring_bytes(""), amqp_cstring_bytes("test_workmode_queue"), 0, 0, NULL, messageBody);

		printf("Thread: %d Send: %s\n", this_thread::get_id(), messageBuf);
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

	WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT = 1;
	return WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT;
}

int workQueueMode_ConsumeThreadFunc()
{
	/*创建与RabbitMQ Server的连接    **/
	amqp_connection_state_t pConn = amqp_new_connection();
	if (NULL == pConn)
	{
		WORK_QUEUE_MODE_CONSUME_THREAD_RESULT_lock.lock();
		WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT = -1;
		WORK_QUEUE_MODE_CONSUME_THREAD_RESULT_lock.unlock();

		return WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT;
	}

	/*创建与RabbitMQ Server通信的socket    **/
	amqp_socket_t* pSocket = amqp_tcp_socket_new(pConn);
	if (NULL == pSocket)
	{
		WORK_QUEUE_MODE_CONSUME_THREAD_RESULT_lock.lock();
		WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT = -1;
		WORK_QUEUE_MODE_CONSUME_THREAD_RESULT_lock.unlock();

		return WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT;
	}

	/*打开与RabbitMQ Server通信的socket    **/
	string hostName = RabbitmqServer::sServerIpAddr;
	int port = RabbitmqServer::iServerPort;
	int openSocketRet = amqp_socket_open(pSocket, hostName.c_str(), port);
	if (AMQP_STATUS_OK != openSocketRet)
	{
		WORK_QUEUE_MODE_CONSUME_THREAD_RESULT_lock.lock();
		WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT = -1;
		WORK_QUEUE_MODE_CONSUME_THREAD_RESULT_lock.unlock();

		return WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT;
	}

	/*登录RabbitMQ Server    **/
	amqp_rpc_reply_t loginRet = amqp_login(pConn, "qhVHost", AMQP_DEFAULT_MAX_CHANNELS, AMQP_DEFAULT_FRAME_SIZE, 0, AMQP_SASL_METHOD_PLAIN, "quhan", "qhmm19971120");
	if (AMQP_RESPONSE_NORMAL != loginRet.reply_type)
	{
		WORK_QUEUE_MODE_CONSUME_THREAD_RESULT_lock.lock();
		WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT = -1;
		WORK_QUEUE_MODE_CONSUME_THREAD_RESULT_lock.unlock();

		return WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT;
	}

	/*打开通信管道    **/
	int channelId = 1;
	amqp_channel_open_ok_t* openChannelRet = amqp_channel_open(pConn, channelId);

	/*消费消息    **/
	while (true)
	{
		amqp_rpc_reply_t getRet = amqp_basic_get(pConn, channelId, amqp_cstring_bytes("test_workmode_queue"), AMQP_RESPONSE_NORMAL);
		if (AMQP_RESPONSE_NORMAL != getRet.reply_type)
			continue;

		amqp_message_t* msg = new amqp_message_t();
		amqp_rpc_reply_t rcvRet = amqp_read_message(pConn, channelId, msg, 0);
		if (AMQP_RESPONSE_NORMAL != rcvRet.reply_type)
		{
			delete msg;
			break;
		}
		else
		{
			printf("Thread: %d Receive: %s\n", this_thread::get_id(), (char *)msg->body.bytes);
			amqp_destroy_message(msg);

			delete msg;
			msg = NULL;

			Sleep(1000);
		}
	}

	/*关闭通信管道    **/
	amqp_channel_close(pConn, channelId, AMQP_REPLY_SUCCESS);

	/*销毁与RabbitM去Server通信的socket    **/
	amqp_connection_close(pConn, AMQP_REPLY_SUCCESS);

	/*释放与RabbitMQ Server连接占用的内存空间    **/
	amqp_maybe_release_buffers(pConn);

	/*销毁与RabbitMQ Server的连接    **/
	amqp_destroy_connection(pConn);

	WORK_QUEUE_MODE_CONSUME_THREAD_RESULT_lock.lock();
	WORK_QUEUE_MODE_PUBLISH_THREAD_RESULT = 1;
	WORK_QUEUE_MODE_CONSUME_THREAD_RESULT_lock.unlock();

	return WORK_QUEUE_MODE_CONSUME_THREAD_RESULT;
}