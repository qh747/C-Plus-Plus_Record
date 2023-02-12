#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*线程池中最大任务容量		**/
#define THREADPOLL_TASKQUEUE_MAX_CAPACITY 1024

/*线程个数					**/
#define THREAD_MAX_SIZE 5

/*线程任务		**/
typedef struct TypeThreadTask
{
	int  arg;							  		/*回调函数参数					**/
	void (*pFuncTask)(int arg);			  		/*回调函数						**/

}ThreadTask;

/*线程池		**/
typedef struct TypeThreadPool
{
	ThreadTask* pTaskQueue;				  		/*任务队列						**/
	int         taskQueueCapacity;		  		/*任务队列总容量				**/
	int         taskQueueSize;			  		/*任务队列当前存在的任务个数	**/
	int 		taskQueuePushPos;		  		/*任务队列插入任务位置			**/
	int 		taskQueuePopPos;		  		/*任务队列弹出任务位置			**/

	pthread_t*  pThreadArray;			  		/*线程数组						**/
	int 		threadArraySize;		  		/*线程数组中的线程个数			**/

	bool		isThreadPoolShutdown;	  		/*线程池是否关闭标志位			**/

	pthread_mutex_t threadPoolLock;		  		/*线程池互斥锁					**/
	pthread_cond_t  threadPoolEmptyCond;  		/*线程池中是否无任务条件变量	**/
	pthread_cond_t  threadPoolNotEmptyCond;	  	/*线程池中是否有任务条件变量	**/

}ThreadPool;


/*创建线程池函数		**/
ThreadPool* funcCreateThreadPool(int queueCapacity, int threadSize);

/*销毁线程池函数		**/
void funcDestoryThreadPool(ThreadPool* pThreadPool);

/*线程任务函数			**/
void* funcThreadTask(void* arg);

/*任务处理回调函数		**/
void funcCallback(int arg);

/*添加任务函数			**/
void funcAddTask(void* threreadPoolPtr);


