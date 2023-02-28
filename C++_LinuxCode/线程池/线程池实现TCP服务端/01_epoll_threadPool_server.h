#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

/*线程池任务数组最大个数	**/
#define MAX_TASK_SIZE 1024

/*线程任务结构体	**/
typedef struct Type_ThreadPool_task
{
	int                  fd;
	int					 epfd;
	struct epoll_event*  evs;
	void                 (*pFuncTask)(void* arg);
	void*                arg;
}ThreadPoolTask;

/*线程池结构体		**/
typedef struct Type_ThreadPool
{
	ThreadPoolTask*  pTaskArray;
	int              taskArrayMaxSize;
	int              taskArrayLiveSize;
	int				 taskArrayPushPos;
	int				 taskArrayPopPos;

	pthread_t*       pThreadArray;
	int              threadArraySize;

	bool			 isThreadPoolShutDown;

	pthread_mutex_t  threadPoolLock;
	pthread_cond_t   threadPoolEmptyCond;
	pthread_cond_t   threadPoolFullCond;
}ThreadPool;

/*创建线程池函数		**/
ThreadPool* funcCreateThreadPool(int taskSize, int threadSize);

/*销毁线程池函数		**/
void funcDestoryThreadPool(ThreadPool* pThreadPool);

/*线程池任务处理函数	**/
void* funcThreadTaskProcess(void* arg);

/*线程池添加任务函数	**/
void funcAddTask(ThreadPool* pThreadPool, int epfd, int sockfd, struct epoll_event* pEvent);

/*处理回调函数			**/
void funcProcessCallback(void* arg);

