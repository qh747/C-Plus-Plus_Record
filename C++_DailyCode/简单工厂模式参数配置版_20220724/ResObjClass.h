#pragma once
#include <iostream>
#include <cstring>
#include <string>
using std::cout;
using std::endl;
using std::string;

/*抽象基类    **/
class AbstractResObjClass
{
public:
	inline virtual void showData(const string& data) = 0;
};

/*一号派生类    **/
class NumberOneResObjClass : public AbstractResObjClass
{
public:
	inline virtual void showData(const string& data)
	{
		cout << "In Number One Class. Data Is : " << data << endl;
	}
};

/*二号派生类    **/
class NumberTwoResObjClass : public AbstractResObjClass
{
public:
	inline virtual void showData(const string& data)
	{
		cout << "In Number Two Class. Data Is : " << data << endl;
	}
};