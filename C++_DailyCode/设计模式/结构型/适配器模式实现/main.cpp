#include <iostream>
using namespace std;

class CalculateClass
{
public:		/*原加法函数    **/
	int addValue(int fstVal, int secVal)	
	{
		return fstVal + secVal;
	}
};

class AdapteCalculateClass
{
public:
	AdapteCalculateClass(int fstVal = 0) :m_fixVal(fstVal)
	{
		m_calObj = CalculateClass();
	}

	~AdapteCalculateClass() { }
	void setFixVal(int val) { m_fixVal = val; }

public:		/*单参数接口适配    **/
	int oneAdaptAddValue(int val)
	{
		return m_calObj.addValue(val, m_fixVal);
	}

public:		/*双参数接口适配    **/
	int twoAdaptAddValue(int fstVal, int secVal)
	{
		return m_calObj.addValue(fstVal, secVal);
	}

public:		/*三参数接口适配    **/
	int threeAdaptAddValue(int fstVal, int secVal, int thrVal)
	{
		return m_calObj.addValue(fstVal, secVal + thrVal);
	}

private:
	int m_fixVal;
	CalculateClass m_calObj;
};

int main()
{
	AdapteCalculateClass adptCalObj(10);

	cout << "Use One Param Adapt Func: " << adptCalObj.oneAdaptAddValue(10) << endl;
	cout << "Use Two Param Adapt Func: " << adptCalObj.twoAdaptAddValue(10, 20) << endl;
	cout << "Use Three Param Adapt Func: " << adptCalObj.threeAdaptAddValue(10, 20, 30) << endl;

	system("pause");
	return 0;
}