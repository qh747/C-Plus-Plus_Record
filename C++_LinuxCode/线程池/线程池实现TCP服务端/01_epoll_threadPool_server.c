#include "01_epoll_threadPool_server.h"

/*创建线程池函数        **/
ThreadPool* funcCreateThreadPool(int taskSize, int threadSize)
{
	/*线程池申请内存空间	**/
	ThreadPool* pThreadPool = (ThreadPool *)malloc(sizeof(ThreadPool));

	/*线程池成员初始化		**/
	pThreadPool->pTaskArray = (ThreadPoolTask *)malloc(sizeof(ThreadPoolTask) * taskSize);
	pThreadPool->taskArrayMaxSize = taskSize;
	pThreadPool->taskArrayLiveSize = 0;
	pThreadPool->taskArrayPushPos = 0;
	pThreadPool->taskArrayPopPos = 0;

	pThreadPool->pThreadArray = (pthread_t *)malloc(sizeof(pthread_t) * threadSize);
	pThreadPool->threadArraySize = threadSize;

	pThreadPool->isThreadPoolShutDown = false;

	pthread_mutex_init(&(pThreadPool->threadPoolLock), NULL);
	pthread_cond_init(&(pThreadPool->threadPoolEmptyCond), NULL);
	pthread_cond_init(&(pThreadPool->threadPoolFullCond), NULL);

	/*启动任务线程			**/
	pthread_attr_t threadAttr;
	pthread_attr_init(&threadAttr);
	pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
	
	pthread_t* pThreadArray = pThreadPool->pThreadArray;
	for(int i = 0; i < threadSize; ++i)
	{
		pthread_create(&pThreadArray[i], &threadAttr, funcThreadTaskProcess, (void *)pThreadPool);
	}

	pthread_attr_destroy(&threadAttr);

	return pThreadPool;
}

/*销毁线程池函数        **/
void funcDestoryThreadPool(ThreadPool* pThreadPool)
{
	if(NULL == pThreadPool)
		return;

	/*触发线程池结束标志位	**/
	pThreadPool->isThreadPoolShutDown = true;

	/*触发线程池结束信号	**/
	pthread_cond_broadcast(&(pThreadPool->threadPoolEmptyCond));

	/*销毁线程池成员		**/
	pthread_cond_destroy(&(pThreadPool->threadPoolEmptyCond));
	pthread_cond_destroy(&(pThreadPool->threadPoolFullCond));
	pthread_mutex_destroy(&(pThreadPool->threadPoolLock));

	free(pThreadPool->pTaskArray);
	free(pThreadPool->pThreadArray);

	/*销毁线程池			**/
	free(pThreadPool);
	pThreadPool = NULL;
}

/*线程池任务处理函数    **/
void* funcThreadTaskProcess(void* arg)
{
	ThreadPool* pThreadPool = (ThreadPool *)arg;
	ThreadPoolTask* pTask = (ThreadPoolTask *)malloc(sizeof(ThreadPoolTask));

	bool isCurHasTaskProcess = false;
	while(true)
	{
		pthread_mutex_lock(&(pThreadPool->threadPoolLock));

		while((pThreadPool->taskArrayLiveSize <= 0) && (false == pThreadPool->isThreadPoolShutDown))
		{
			pthread_cond_wait(&(pThreadPool->threadPoolEmptyCond), &(pThreadPool->threadPoolLock));
		}

		/*线程池退出条件被触发		**/
		if(true == pThreadPool->isThreadPoolShutDown)
		{
			free(pTask);
			pthread_mutex_unlock(&(pThreadPool->threadPoolLock));
			pthread_exit(NULL);
		}

		/*判断当前是否有任务		**/
		if(pThreadPool->taskArrayLiveSize > 0)
		{
			/*复制任务内存空间，防止任务处理过程中被覆盖	**/
			int popPos = (pThreadPool->taskArrayPopPos) % (pThreadPool->taskArrayMaxSize);

			memcpy(pTask, &(pThreadPool->pTaskArray[popPos]), sizeof(ThreadPoolTask));
			pTask->arg = pTask;

			/*任务标志位记录	**/
			--(pThreadPool->taskArrayLiveSize);
			++(pThreadPool->taskArrayPopPos);
		
			/*线程同步			**/
			pthread_cond_signal(&(pThreadPool->threadPoolFullCond));
			
			/*当前有任务需要处理标志位置为true		**/
			isCurHasTaskProcess = true;
		}

		pthread_mutex_unlock(&(pThreadPool->threadPoolLock));

		/*任务处理			**/
		if(true == isCurHasTaskProcess)
		{
			pTask->pFuncTask(pTask->arg);

			/*当前有任务需要处理标志位重置		**/
			isCurHasTaskProcess = false;
		}
	}
}

/*处理回调函数          **/
void funcProcessCallback(void* arg)
{
    ThreadPoolTask* pTask = (ThreadPoolTask *)arg;

    char recvBuf[128] = "\0";
    memset(recvBuf, 0, sizeof(recvBuf));

	while(true)		// epoll边沿触发模式下需要循环读取数据，直到将缓冲区的数据读取干净
	{
    	int readSize = read(pTask->fd, recvBuf, sizeof(recvBuf));
    	if(0 == readSize)
    	{
    	    printf("client disconnect\n");
	
	        epoll_ctl(pTask->epfd, EPOLL_CTL_DEL, pTask->fd, pTask->evs);
   		    close(pTask->fd);

			break;
    	}
    	else if(readSize > 0)
    	{
    	    printf("recv: %s", recvBuf);
    	    write(pTask->fd, "server recv success\n", strlen("server recv success\n"));
    	}
		else if(readSize < 0)
		{
			if(EWOULDBLOCK == errno || EAGAIN == errno)
			{
				printf("read data over\n");
			}
			else
			{
				perror("read() error");
				epoll_ctl(pTask->epfd, EPOLL_CTL_DEL, pTask->fd, pTask->evs);
                close(pTask->fd);
			}
			break;
		}

		memset(recvBuf, 0, sizeof(recvBuf));
	}
}

/*线程池添加任务函数    **/
void funcAddTask(ThreadPool* pThreadPool, int epfd, int sockfd, struct epoll_event* pEvent)
{
	pthread_mutex_lock(&(pThreadPool->threadPoolLock));
	while((pThreadPool->taskArrayLiveSize >= pThreadPool->taskArrayMaxSize) && (false == pThreadPool->isThreadPoolShutDown))
	{
		pthread_cond_wait(&(pThreadPool->threadPoolFullCond), &(pThreadPool->threadPoolLock));
	}

	if(true == pThreadPool->isThreadPoolShutDown)
	{
		pthread_mutex_unlock(&(pThreadPool->threadPoolLock));
		return;
	}

	/*获取向任务队列添加任务的位置	**/
	int pushPos = (pThreadPool->taskArrayPushPos) % (pThreadPool->taskArrayMaxSize);
	
	/*获取指定位置的任务			**/
	ThreadPoolTask* pTempTask = &(pThreadPool->pTaskArray[pushPos]);
	pTempTask->epfd = epfd;
	pTempTask->fd = sockfd;
	pTempTask->evs = pEvent;
	pTempTask->pFuncTask = funcProcessCallback;
	pTempTask->arg = pTempTask;

	/*任务标志位记录    			**/
	++(pThreadPool->taskArrayPushPos);
	++(pThreadPool->taskArrayLiveSize);

	/*线程同步						**/
	pthread_mutex_unlock(&(pThreadPool->threadPoolLock));
	pthread_cond_signal(&(pThreadPool->threadPoolEmptyCond));
}

int main()
{
	/*创建线程池	**/
	ThreadPool* pThreadPool = funcCreateThreadPool(MAX_TASK_SIZE, 10);
	
	/*创建socket套接字	**/
	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	/*绑定IP地址和端口	**/
	struct sockaddr_in sockAddr;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(8000);
	sockAddr.sin_addr.s_addr = inet_addr("192.168.1.106");

	int bindRet = bind(sockfd, (struct sockaddr *)&sockAddr, sizeof(sockAddr));

	/*监听socket套接字	**/
	int listenRet = listen(sockfd, 4);

	/*创建epoll，处理sokcet请求		**/
	int epfd = epoll_create(1);

	struct epoll_event epEvent;
	epEvent.data.fd = sockfd;
	epEvent.events = EPOLLIN;

	epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &epEvent);

	/*处理请求的服务端	**/
	struct epoll_event epEventArray[32];
	memset(epEventArray, 0, sizeof(epEventArray));

	while(true)
	{
		int readySize = epoll_wait(epfd, epEventArray, 32, -1);
		if(readySize <= 0)
			continue;

		for(int j = 0; j < readySize; ++j)
		{
			if((sockfd == epEventArray[j].data.fd) && (EPOLLIN & epEventArray[j].events))
			{
				/*新客户端接入	**/
				struct sockaddr_in clientAddr;
				socklen_t addrSize = sizeof(clientAddr);

				int clientfd = accept(sockfd, (struct sockaddr *)&clientAddr, &addrSize);
				if(-1 == clientfd)
					continue;
	
				/*socket套接字设置为非阻塞读取		**/
				int socketAttr = fcntl(clientfd, F_GETFL, 0);
				fcntl(clientfd, F_SETFL, socketAttr | SOCK_NONBLOCK);

				char ipBuf[16] = "\0";
			    inet_ntop(AF_INET, &clientAddr.sin_addr, ipBuf, INET_ADDRSTRLEN);
		   		
		 		int port = ntohs(clientAddr.sin_port);
				printf("new client connect. ip: %s port: %d\n", ipBuf, port);

				/*新客户端加入epoll 	**/
				struct epoll_event epClientEvent;
				memset(&epClientEvent, 0, sizeof(epClientEvent));

				epClientEvent.data.fd = clientfd;
				epClientEvent.events = EPOLLIN | EPOLLET;

				epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &epClientEvent);		
			}
			else if(sockfd != epEventArray[j].data.fd)
			{
				/*与客户端通信	**/
				funcAddTask(pThreadPool, epfd, epEventArray[j].data.fd, &epEventArray[j]);
			}
		}
		
		memset(epEventArray, 0, sizeof(epEventArray));
	}

	sleep(1);

	funcDestoryThreadPool(pThreadPool);
	close(sockfd);

	return 0;
}
