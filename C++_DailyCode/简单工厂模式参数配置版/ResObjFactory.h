#pragma once
#include <map>
#include "ResObjClass.h" 
using std::map;
using std::make_pair;
typedef void* (*objCreateFunc)();	/*资源类对象构造函数    **/

class ResObjCreateFactory
{
public:
	static void registerClass(const string& className, objCreateFunc objCreateFuncPtr)
	{
		/*所有类只允许注册一次    **/
		if (getObjMap().end() == getObjMap().find(className))
		{
			getObjMap().insert(make_pair(className, objCreateFuncPtr));
		}
	}

	static void* createObject(const string& className)
	{
		AbstractResObjClass* resObjPtr = NULL;
		if (getObjMap().end() == getObjMap().find(className))
		{
			return NULL;
		}
		else
		{
			/*从创建类对象的map映射表中的键值对找到创建函数指针，通过函数指针解引用找到函数，通过函数创建对象    **/
			resObjPtr = static_cast<AbstractResObjClass*>((*(getObjMap().find(className)->second))());
			return resObjPtr;
		}
	}

private:
	inline static map<string, objCreateFunc>& getObjMap()
	{
		/*资源类对象和类名称映射函数    **/
		static map<string, objCreateFunc> objMap;
		return objMap;
	}

};