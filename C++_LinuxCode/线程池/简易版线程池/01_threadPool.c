#include "01_threadPool.h"

/*初始化全局线程池		**/
ThreadPool* GBL_PTR_TRDPOOL = NULL;

/*创建线程池函数    **/
ThreadPool* funcCreateThreadPool(int queueCapacity, int threadSize)
{
	/*申请堆区空间给线程池指针		**/
	GBL_PTR_TRDPOOL = (ThreadPool *)malloc(sizeof(ThreadPool));

	/*线程池初始化		**/
	memset(GBL_PTR_TRDPOOL, 0, sizeof(ThreadPool));

	GBL_PTR_TRDPOOL->pTaskQueue = (ThreadTask *)malloc(queueCapacity * sizeof(ThreadTask));
	GBL_PTR_TRDPOOL->taskQueueCapacity = queueCapacity;
	GBL_PTR_TRDPOOL->taskQueueSize = 0;
	GBL_PTR_TRDPOOL->taskQueuePushPos = 0;
	GBL_PTR_TRDPOOL->taskQueuePopPos = 0;

	GBL_PTR_TRDPOOL->pThreadArray = (pthread_t *)malloc(threadSize * sizeof(pthread_t));
	GBL_PTR_TRDPOOL->threadArraySize = threadSize;

	GBL_PTR_TRDPOOL->isThreadPoolShutdown = false;

	pthread_mutex_init(&(GBL_PTR_TRDPOOL->threadPoolLock), NULL);
	pthread_cond_init(&(GBL_PTR_TRDPOOL->threadPoolEmptyCond), NULL);
	pthread_cond_init(&(GBL_PTR_TRDPOOL->threadPoolNotEmptyCond), NULL);

	/*创建执行任务的线程	**/
	pthread_attr_t threadAttribute;
	pthread_attr_init(&threadAttribute);
	pthread_attr_setdetachstate(&threadAttribute, PTHREAD_CREATE_DETACHED);

	pthread_t* tmpThreadPtr = GBL_PTR_TRDPOOL->pThreadArray;
	for(int i = 0; i < threadSize; ++i)
	{
		pthread_create(&(tmpThreadPtr[i]), &threadAttribute, funcThreadTask, (void *)GBL_PTR_TRDPOOL);
	}

	pthread_attr_destroy(&threadAttribute);

	/*返回线程池指针		**/
	return GBL_PTR_TRDPOOL;
}

/*销毁线程池函数        **/
void funcDestoryThreadPool(ThreadPool* pThreadPool)
{
	if(NULL == pThreadPool)
		return;

	pThreadPool->isThreadPoolShutdown = true;
	pthread_cond_broadcast(&(pThreadPool->threadPoolEmptyCond));
	pthread_cond_broadcast(&(pThreadPool->threadPoolNotEmptyCond));

	pthread_cond_destroy(&(pThreadPool->threadPoolEmptyCond));
	pthread_cond_destroy(&(pThreadPool->threadPoolNotEmptyCond));
	pthread_mutex_destroy(&(pThreadPool->threadPoolLock));

	free(pThreadPool->pThreadArray);
	free(pThreadPool->pTaskQueue);
	free(pThreadPool);

	pThreadPool = NULL;
	return;
}

/*线程任务函数  **/
void* funcThreadTask(void* arg)
{
	ThreadPool* pThreadPool = (ThreadPool *)arg;
	ThreadTask* pTask = (ThreadTask *)malloc(sizeof(ThreadTask));
	int taskPos = -1;

	while(true)
	{		
		pthread_mutex_lock(&(pThreadPool->threadPoolLock));
	
		while((pThreadPool->taskQueueSize <= 0) && (false == pThreadPool->isThreadPoolShutdown))
		{
			pthread_cond_wait(&(pThreadPool->threadPoolNotEmptyCond), &(pThreadPool->threadPoolLock));
		}	

		/*如果线程池关闭就退出任务处理函数		**/
		if(true == pThreadPool->isThreadPoolShutdown)
			break;

		/*从任务队列中取出任务进行处理		**/
		taskPos = pThreadPool->taskQueuePopPos % pThreadPool->taskQueueCapacity;
		++pThreadPool->taskQueuePopPos;

		memcpy(pTask, &(pThreadPool->pTaskQueue[taskPos]), sizeof(ThreadTask));
		--pThreadPool->taskQueueSize;

		pthread_mutex_unlock(&(pThreadPool->threadPoolLock));
		pthread_cond_signal(&(pThreadPool->threadPoolEmptyCond));
		
		/*处理任务		**/
		pTask->pFuncTask(pTask->arg);
	}

	pthread_mutex_unlock(&(pThreadPool->threadPoolLock));
	free(pTask);
	return NULL;
}

/*任务处理回调函数      **/
void funcCallback(int arg)
{
	printf("thread process. thread id: %ld value: %d\n", pthread_self(), arg);
}

/*添加任务函数          **/
void funcAddTask(void* threadPoolPtr)
{
	ThreadPool* pThreadPool = (ThreadPool *)threadPoolPtr;
	if(NULL == pThreadPool)
	{
		printf("error: pThreadPool is NULL\n");
		return;
	}

	int addTaskCount = 0;
	while(true)
	{
		pthread_mutex_lock(&(pThreadPool->threadPoolLock));

		while(pThreadPool->taskQueueSize >= pThreadPool->taskQueueCapacity)
		{
			pthread_cond_wait(&(pThreadPool->threadPoolEmptyCond), &(pThreadPool->threadPoolLock));
		}

		if(true == pThreadPool->isThreadPoolShutdown)
			break;

		int taskPos = pThreadPool->taskQueuePushPos % pThreadPool->taskQueueCapacity;
		++pThreadPool->taskQueuePushPos;

		pThreadPool->pTaskQueue[taskPos].pFuncTask = funcCallback;
		pThreadPool->pTaskQueue[taskPos].arg = addTaskCount;

		printf("thread generate. therad id: %ld value: %d\n", pthread_self(), addTaskCount);

		++addTaskCount;
		++pThreadPool->taskQueueSize;

		pthread_mutex_unlock(&(pThreadPool->threadPoolLock));
		pthread_cond_signal(&(pThreadPool->threadPoolNotEmptyCond));
		
		sleep(1);
	}

	pthread_mutex_unlock(&(pThreadPool->threadPoolLock));
}

/*添加任务函数单独放到另一个子线程处理		**/
void* threadFunc(void* arg)
{
    funcAddTask(arg);

    return NULL;
}

int main()
{
    ThreadPool* pThreadPool = funcCreateThreadPool(THREADPOLL_TASKQUEUE_MAX_CAPACITY, 3);

    pthread_t generateThreadId;
    pthread_create(&generateThreadId, NULL, threadFunc, (void *)pThreadPool);
    pthread_detach(generateThreadId);

    sleep(20);
	
    funcDestoryThreadPool(pThreadPool);
    return 0;
}
