#include <iostream>
#include "libRabbitMQTest.h"
using namespace std;

int main()
{
	/*简单模式测试    **/
	//simpleModeFunc();     

	/*工作队列模式    **/
	//workQueueModeFunc();

	/*发布/订阅者模式    **/
	//pubAndSubModeFunc();

	/*路由模式    **/
	routeModeFunc();

	return 0;
}
