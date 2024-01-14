#include "InsertSearch.h"

/*插值查找												**/
void funcCallInsertSort()
{
	/*第一组数据测试									**/
	vector<int> fstIntVec = initializer_list<int>{ 1000, 300, 20, 10000, 5, 45, 789 ,856 };
	funcChooseSort(fstIntVec);
	cout << "First Test Vec: ";
	for_each(fstIntVec.begin(), fstIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << "Val " << 45 << " In ";

	int fstValIndex = funcInsertSort(fstIntVec, 45);
	cout << fstValIndex << endl << endl;

	/*第二组数据测试												**/
	vector<int> secIntVec = initializer_list<int>{ 60, 70, 101, 5, 2, 999, 1100, 0 };
	funcChooseSort(secIntVec);
	cout << "Second Test Vec: ";
	for_each(secIntVec.begin(), secIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << "Val " << 1100 << " In ";

	int secValIndex = funcInsertSort(secIntVec, 1100);
	cout << secValIndex << endl << endl;

	/*第三组数据测试												**/
	vector<int> trdIntVec = initializer_list<int>{ 1, 2, 5, 7, 2, 4, 6 ,8 };
	funcChooseSort(trdIntVec);
	cout << "Third Test Vec: ";
	for_each(trdIntVec.begin(), trdIntVec.end(), [](const int& val) { cout << val << " "; });
	cout << endl << "Val " << 1 << " In ";

	int trdValIndex = funcInsertSort(trdIntVec, 1);
	cout << trdValIndex << endl << endl;
}

int funcInsertSort(vector<int>& vec, int val)
{
	if (vec.empty())
		return -1;

	int startPos = 0;
	int endPos = vec.size() - 1;
	
	/*中间位置为：起始位置 + 当前元素在整个数组中所在位置的比例 * 数组中的元素个数						**/
	int midPos = startPos + ((val - vec[startPos]) / (vec[endPos] - vec[startPos])) * (endPos - startPos);

	while (startPos <= endPos)
	{
		if (vec[midPos] == val)
			return midPos;
		else if (vec[midPos] > val)
			endPos = midPos - 1;
		else
			startPos = midPos + 1;

		/*找到当前子数组中给定元素的比例范围															**/
		midPos = startPos + ((val - vec[startPos]) / (vec[endPos] - vec[startPos])) * (endPos - startPos);
	}

	/*当前数组中未找到给定元素																			**/
	return -1;
}