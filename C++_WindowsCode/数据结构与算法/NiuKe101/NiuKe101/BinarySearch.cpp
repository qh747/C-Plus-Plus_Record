#include "BinarySearch.h"

int search_Solution::search(vector<int>& nums, int target)
{
	if (nums.empty())
		return -1;

	int start = 0;
	int end = nums.size() - 1;
	while (start <= end)
	{
		int mid = (start + end) / 2;
		if (target < nums[mid])
		{
			// 目标元素在区间中间节点前，将末尾位置移动至之中间位置前
			end = mid - 1;
		}	
		else if (target > nums[mid])
		{
			// 目标元素在区间中间节点后，将开始位置移动至之中间位置后
			start = mid + 1;
		}		
		else
		{
			// 找到目标位置
			return mid;
		}							
	}

	// 未找到目标位置
	return -1;
}

void search_Solution::searchTest()
{
	vector<int> vec{ 1, 3, 5, 7, 9 };
	int target = 6;

	int idx = this->search(vec, target);
	cout << idx << endl;
}

int findPeakElement_Solution::findPeakElement(vector<int>& nums)
{
	if (nums.empty())
		return -1;

	int start = 0;
	int end = nums.size() - 1;
	
	while (start < end)
	{
		int mid = (start + end) / 2;
		if (nums[mid] < nums[mid + 1])
		{
			// 前一个值比后一个值小，说明峰值在右边区间
			start = mid + 1;
		}
		else
		{
			// 前一个值比后一个值大，说明当前节点有可能为峰值
			end = mid;
		}
	}
	return end;
}

void findPeakElement_Solution::findPeakElementTest()
{
	vector<int> vec{ 42, 33, 25, 17, 9 };

	int idx = this->findPeakElement(vec);
	cout << idx << endl;
}

int InversePairs_Solution::InversePairs(vector<int>& nums)
{
	int size = nums.size();
	if (size < 2)
		return 0;

	// 使用归并排序统计逆序对
	int count = 0;
	mergeSplit(nums, 0, size - 1, count);
	return count;
}

void InversePairs_Solution::mergeSplit(vector<int>& nums, int start, int end, int& count)
{
	if (start >= end)
		return;

	int mid = (start + end) / 2;
	mergeSplit(nums, start, mid, count);
	mergeSplit(nums, mid + 1, end, count);
	merge(nums, start, end, count);
}

void InversePairs_Solution::merge(vector<int>& nums, int start, int end, int& count)
{
	if (start >= end)
		return;

	vector<int> curVec;
	int curStart = start;
	int mid = (start + end) / 2;
	int nextStart = mid + 1;
	while (curStart <= mid && nextStart <= end)
	{
		if (nums[curStart] > nums[nextStart])
		{
			/*
			 *	因为此时前半部分和后半部分数组有序，当前半部分指向curStart的元素大于后半部分指向nextStart的元素时，
			 *  前半部分curStart - mid位置的元素都大于后半部分指向nextStart，
			 *	因此逆序对需要统计curStart - mid区间，因为区间为前开后闭，需要+1统计最后一个元素
			*/
			count += (mid - curStart + 1);
			count %= 1000000007;					// 题目规定要对结果进行1000000007求余数
			curVec.push_back(nums[nextStart++]);
		}
		else
			curVec.push_back(nums[curStart++]);
	}

	while (curStart <= mid)
	{
		curVec.push_back(nums[curStart++]);	
	}

	while (nextStart <= end)
	{
		curVec.push_back(nums[nextStart++]);
	}

	for (int i = start, j = 0; i <= end; ++i, ++j)
	{
		nums[i] = curVec[j];
	}
}

void InversePairs_Solution::InversePairsTest()
{
	vector<int> vec{ 364,637,341,406,747,995,234,971,571,219,993,407,416,
		366,315,301,601,650,418,355,460,505,360,965,516,648,727,667,465,
		849,455,181,486,149,588,233,144,174,557,67,746,550,474,162,268,142,
		463,221,882,576,604,739,288,569,256,936,275,401,497,82,935,983,583,
		523,697,478,147,795,380,973,958,115,773,870,259,655,446,863,735,784,
		3,671,433,630,425,930,64,266,235,187,284,665,874,80,45,848,38,811,
		267,575 };

	int count = this->InversePairs(vec);
	cout << count << endl;
}

int minNumberInRotateArray_Solution::minNumberInRotateArray(vector<int>& nums)
{
	int size = nums.size();
	if (size < 2)
		return 0;

	int start = 0; 
	int end = size - 1;
	int mid = (start + end) / 2;	// 通过mid将数组划分为两个有序数组
	while (start <= end)
	{
		if (nums[mid] > nums[end])	
			start = mid + 1;	// 查找前一个有序数组的右边界
		else if (nums[mid] == nums[end])
			--end;	// 前后两个有序数组的值相同，向前移动后个数组的右边界
		else
			end = mid;	// 查找后个数组的起始值

		mid = (start + end) / 2;
	}

	return nums[start];
}

void minNumberInRotateArray_Solution::minNumberInRotateArrayTest()
{
	vector<int> vec{ 4, 5, 6, 1, 2, 3 };

	int idx = this->minNumberInRotateArray(vec);
	cout << idx << endl;
}

int compare_Solution::compare(string version1, string version2)
{
	int v1Len = version1.size();
	int v2Len = version2.size();

	int v1Idx = 0;
	int v2Idx = 0;
	while (v1Idx < v1Len || v2Idx < v2Len)
	{
		int v1Val = 0;
		int v2Val = 0;

		while (v1Idx < v1Len && '.' != version1[v1Idx])
		{
			v1Val = v1Val * 10 + (version1[v1Idx++] - '0');
		}
		++v1Idx;

		while (v2Idx < v2Len && '.' != version2[v2Idx])
		{
			v2Val = v2Val * 10 + (version2[v2Idx++] - '0');
		}
		++v2Idx;

		if (v1Val != v2Val)
			return (v1Val > v2Val) ? 1 : -1;
	}

	return 0;
}

void compare_Solution::compareTest()
{
	string v1 = "1.01.2.3";
	string v2 = "1.01.2.3.1";

	cout << this->compare(v1, v2) << endl;
}