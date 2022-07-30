#include <iostream>
#include <functional>
using namespace std;

/*仿函数std::function类型定义，指向参数是int和int，返回值是int的函数    **/
typedef std::function<int(int, int)> MyFunction;

/*普通函数    **/
int addFunc(int fstNum, int secNum)
{
	return fstNum + secNum;
}

/*lambda表达式    **/
auto lambda = [](int fstNum, int secNum) {return fstNum + secNum; };

/*函数对象    **/
struct MyAddType
{
	int operator()(int fNum, int sNum)
	{
		return fNum + sNum;
	}
};

/*函数对象    **/
class MyAddClass
{
public:
	int myAddFunc(int fNum, int sNum)
	{
		return fNum + sNum;
	}
};

int main()
{
	MyFunction funcObj;

	funcObj = addFunc;
	cout << "指向普通函数" << endl;
	cout << funcObj(10, 20) << endl;

	funcObj = lambda;
	cout << "指向lambda" << endl;
	cout << funcObj(10, 20) << endl;

	funcObj = MyAddType();
	cout << "指向函数对象" << endl;
	cout << funcObj(10, 20) << endl;

	MyAddClass myAddObj;
	funcObj = std::bind(&MyAddClass::myAddFunc, &myAddObj, 10,20);
	cout << "指向成员函数" << endl;
	cout << funcObj(10, 20) << endl;

	system("pause");
	return 0;
}