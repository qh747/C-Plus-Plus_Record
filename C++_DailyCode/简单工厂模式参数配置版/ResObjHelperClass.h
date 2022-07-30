#pragma once
#include "ResObjFactory.h"

/*派生类的帮助类，以定义宏的形式声明类和创建类对象    **/			     
#define REG_CLASS(class_Name)                                             \
class class_Name##HelperClass                                             \
{                                                                         \
public:                                                                   \
	class_Name##HelperClass()                                             \
	{                                                                     \
		ResObjCreateFactory::registerClass(#class_Name, createResObject); \
	}								                                      \
									                                      \
public:								                                      \
	static void* createResObject()		                                  \
	{								                                      \
		return new class_Name;		                                      \
	}	                                                                  \
};									                                      \
                                                                          \
class_Name##HelperClass class_Name##HelperObj;       