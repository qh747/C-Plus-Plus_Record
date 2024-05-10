#include "BlockSearch.h"

/*分块查找												**/
void funcCallBlockSort()
{
	vector<int> intVec = initializer_list<int>{ 0, 3, 2, 5,  9, 6, 7 ,8,  45, 10, 32, 27,  78, 91, 73, 99 };
	vector<Index_dt> idxVec = initializer_list<Index_dt>{ Index_dt(5, 0), Index_dt(9, 4), Index_dt(45, 8), Index_dt(99, 12) };

	cout << "Test Vec: ";
	for_each(intVec.begin(), intVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl;

	/*第一组数据测试												**/
	cout << "Val " << 32 << " In ";
	int fstValIndex = funcBlockSort(intVec, idxVec, 32);
	cout << fstValIndex << endl;

	/*第二组数据测试												**/
	cout << "Val " << 0 << " In ";
	int secValIndex = funcBlockSort(intVec, idxVec, 0);
	cout << secValIndex << endl;

	/*第三组数据测试												**/
	cout << endl << "Val " << 99 << " In ";
	int trdValIndex = funcBlockSort(intVec, idxVec, 99);
	cout << trdValIndex << endl;
}

int funcBlockSort(const vector<int>& vec, const vector<Index_dt>& idxVec, int keyVal)
{
	/*根据索引表和给定值查找起始查找索引和结束查找索引	**/
	int bolckStartIndex = -1;
	int bolckEndIndex = -1;
	for (int i = 0; i < idxVec.size(); ++i)
	{
		if (idxVec[i].iVal >= keyVal)
		{
			/*设定查找范围的起始索引					**/
			bolckStartIndex = idxVec[i].iIndex;

			/*设定查找范围的结束索引					**/
			if (i != idxVec.size() - 1)
				bolckEndIndex = idxVec[i + 1].iIndex;
			else
				bolckEndIndex = vec.size() - 1;

			break;
		}
	}

	/*起始索引或结束索引设置异常						**/
	if (-1 == bolckStartIndex || -1 == bolckEndIndex)
		return -1;

	/*根据起始索引和结束索引查找给定值的索引			**/
	for (int j = bolckStartIndex; j <= bolckEndIndex; ++j)
	{
		if (vec[j] == keyVal)
			return j;
	}

	/*查找失败											**/
	return -1;
}