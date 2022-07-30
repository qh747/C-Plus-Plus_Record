#pragma once
#include <functional>
#include <memory>
#include <map>
#include "ResourceClass.h"
using namespace std;

/*BASIC_RESOURCE_TYPE为基类    **/
template <typename BASIC_RESOURCE_TYPE>	
class IocContainer
{
public:
	IocContainer() { }
	~IocContainer() { }

public:
	/*INHERIT_RESOURCE为派生类的类型    **/
	template <typename INHERIT_RESOURCE_TYPE>	
	void registerType(string strKey)
	{
		/*创建函数对象，指向派生类的构造函数，并通过new创建一个对象    **/
		function<BASIC_RESOURCE_TYPE* ()> func = []() { return new INHERIT_RESOURCE_TYPE(); };
		/*注册派生类类型名称和创建派生类指针对象的函数    **/
		innerRegisterType(strKey, func);
	}

	shared_ptr<BASIC_RESOURCE_TYPE> resolve(string strKey)
	{
		/*返回派生类指针对象    **/
		return shared_ptr<BASIC_RESOURCE_TYPE>(innerResolve(strKey));
	}

private:
	void innerRegisterType(string strKey, function<BASIC_RESOURCE_TYPE* ()> funcValue)
	{
		/*查找派生类的类型标识是否被注册过    **/
		if (m_containMap.end() == m_containMap.find(strKey))
			m_containMap.insert(make_pair(strKey, funcValue));
	}

	BASIC_RESOURCE_TYPE* innerResolve(string strKey)
	{
		typename map<string, function<BASIC_RESOURCE_TYPE* ()>>::iterator iter = m_containMap.find(strKey);
		if (m_containMap.end() == iter)
			return NULL;
		else
			return iter->second();	/*加()是直接通过调用函数创建派生类对象    **/
	}

private:
	/*key为类的唯一标识或类型名称    **/
	/*value为new类对象的函数    **/
	map<string, function<BASIC_RESOURCE_TYPE* ()>> m_containMap;
};
