#pragma once
#include "ResObjHelperClass.h"

/*注册一号资源类    **/
REG_CLASS(NumberOneResObjClass)

class AutoFactory
{
public:
	static AbstractResObjClass* createOne()
	{
		/*创建一号资源类    **/
		return static_cast<AbstractResObjClass *>(ResObjCreateFactory::createObject("NumberOneResObjClass"));
	}
};

/*之后如果需要创建二号资源类，只需要修改注注册资源类的宏定义和创建类对象的参数    **/