#include <iostream>
#include <cstring>
#include <string>
using namespace std;

/*基类的函数和虚函数是否会被子类覆盖测试    **/
class TestBasicClass
{
/*普通函数    **/
public:
	void simpleShowValue(int val)
	{
		cout << "In Basic Class Simple Function, Int Type Value : " << val << endl;
	}

	void simpleShowValue(string val)
	{
		cout << "In Basic Class Simple Function, String Type Value : " << val << endl;
	}

/*虚函数    **/
public:
	virtual void virtualShowValue(int val)
	{
		cout << "In Basic Class Virtual Function, Int Type Value : " << val << endl;
	}

	virtual void virtualShowValue(string val)
	{
		cout << "In Basic Class Virtual Function, String Type Value : " << val << endl;
	}
};

class TestInheritClass :public TestBasicClass
{
public:
	using TestBasicClass::virtualShowValue;    /*根据Effective C++，测试参数类型为string的虚函数是否会被隐藏*/

/*普通函数    **/
public:
	void simpleShowValue(int val)	/*只继承参数类型为int的函数，测试是否会隐藏参数为string的重载函数    **/
	{
		cout << "In Herit Class Simple Function, Int Type Value : " << val << endl;
	}

/*虚函数    **/
public:
	virtual void virtualShowValue(int val)    /*只继承参数类型为int的函数，测试是否会隐藏参数为string的重载函数    **/
	{
		cout << "In Herit Class Virtual Function, Int Type Value : " << val << endl;
	}
};

int main()
{
	/*创建类对象形式测试   **/
	TestInheritClass testInheritObj;
	testInheritObj.simpleShowValue(10);
	testInheritObj.virtualShowValue(20);
	testInheritObj.virtualShowValue("hello");

	/*创建对象形式派生类会隐藏基类的重载函数    **/
	/*使用using TestBasicClass::virtualShowValue的重载函数不会被隐藏    **/
 
	/*创建指针型形式测试    **/
	TestBasicClass* testInheritPtr = new TestInheritClass();
	testInheritPtr->simpleShowValue(100);
	testInheritPtr->simpleShowValue("Hello");
	testInheritPtr->virtualShowValue(200);
	testInheritPtr->virtualShowValue("Hello");

	/*创建指针形式派生类不会隐藏基类的重载函数    **/

	system("pause");
	return 0;
}