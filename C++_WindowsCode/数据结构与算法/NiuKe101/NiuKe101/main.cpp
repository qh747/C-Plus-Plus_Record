#include "LinkList.h"
#include "BinarySearch.h"
#include "BinaryTree.h"
#include "HeapStackQueue.h"
#include "HashAlg.h"

// 链表测试函数
void fundLinkTest() 
{
	// 反转链表
	// ReverseLinkList_Solution solu;
	// solu.ReverseListTest();

	// 链表内指定区间反转
	// ReverseBetween_Solution solu;
	// solu.ReverseBetweenTest();

	// 合并两个排序的链表
	// Merge_Solution solu;
	// solu.MergeTest();

	// 合并K个已排序的链表
	// mergeKLists_Solution solu;
	// solu.mergeKListsTest();

	// 判断链表中是否有环
	// HasCycle_Solution solu;
	// solu.hasCycleTest();

	// 链表中环的入口节点
	// EntryNodeOfLoop_Solution solu;
	// solu.EntryNodeOfLoopTest();

	// 链表中倒数最后K个节点
	// FindKthToTail_Solution solu;
	// solu.FindKthToTailTest();

	// 两个链表的第一个公共节点
	// FindFirstCommonNode_Solution solu;
	// solu.FindKthToTailTest();

	// 链表相加（二）
	// addInList_Solution solu;
	// solu.addInListTest();

	// 单链表的排序
	// sortInList_Solution solu;
	// solu.sortInListTest();

	// 判断一个链表是否为回文结构
	// isPail_Solution solu;
	// solu.isPailTest();

	// 链表的奇偶重排
	// oddEvenList_Solution solu;
	// solu.oddEvenListTest();

	// 删除有序链表中重复的元素-I
	// deleteDuplicates_Solution solu;
	// solu.deleteDuplicatesTest();

	// 删除有序链表中重复的元素-II
	// deleteDuplicatesII_Solution solu;
	// solu.deleteDuplicatesIITest();
}

// 二分查找测试函数
void binarySearchTest() 
{
	// BM1 - 二分查找-I
	// search_Solution solu;
	// solu.searchTest();

	// BM3 - 寻找峰值
	// findPeakElement_Solution solu;
	// solu.findPeakElementTest();

	// BM4 - 数组中的逆序对
	// InversePairs_Solution solu;
	// solu.InversePairsTest();

	// BM5 - 旋转数组的最小数字
	// minNumberInRotateArray_Solution solu;
	// solu.minNumberInRotateArrayTest();

	// BM6 - 比较版本号
	compare_Solution solu;
	solu.compareTest();
}

// 二叉树测试函数
void binaryTreeTest() 
{
	// BM1 - 二叉树的前序遍历
	// preorderTraversal_Solution solu;
	// solu.preorderTraversalTest();

	// BM2  -二叉树的中序遍历
	// inorderTraversal_Solution solu;
	// solu.inorderTraversalTest();

	// BM3  -二叉树的后序遍历
	// postorderTraversal_Solution solu;
	// solu.postorderTraversalTest();

	// BM6 - 二叉树的最大深度
	// maxDepth_Solution solu;
	// solu.maxDepthTest();

	// BM8 - 二叉搜索树与双向链表
	// Convert_Solution solu;
	// solu.ConvertTest();

	// BM10 - 合并二叉树
	// mergeTrees_Solution solu;
	// solu.mergeTreesTest();

	// BM11 - 二叉树的镜像
	// Mirror_Solution solu;
	// solu.MirrorTest();

	// BM12 - 判断是否为二叉搜索树
	// isValidBST_Solution solu;
	// solu.isValidBSTTest();

	// BM13 - 判断是否为完全二叉树
	// isCompleteTree_Solution solu;
	// solu.isCompleteTreeTest();

	// BM14 - 判断是否为平衡二叉树
	// IsBalancedTree_Solution solu;
	// solu.IsBalancedTreeTest();

	// BM15 - 二叉搜索树的公共祖先
	// lowestCommonAncestor_Solution solu;
	// solu.lowestCommonAncestorTest();

	// BM17 - 序列化二叉树
	// Serialize_Solution solu;
	// solu.demo();

	// BM18 - 重建二叉树
	// reConstructBinaryTree_Solution solu;
	// solu.demo();

	// BM19 - 二叉树的右视图
	// solve_Solution solu;
	// solu.demo();
}

// 堆/栈/链表测试函数
void heapStackQueueTest()
{
	// BM1 - 用两个栈实现队列
	// TwoStackImplQueue_Solution solu;
	// solu.demo();

	// BM2 - 包含min函数的栈
	// IncludeMinStack_Solution solu;
	// solu.demo();

	// BM3 - 有效括号序列
	// isValid_Solution solu;
	// solu.demo();

	// BM4 - 滑动窗口的最大值
	// maxInWindows_Solution solu;
	// solu.demo();

	// BM5 - 最小的K个数
	// GetLeastNumbers_Solution solu;
	// solu.demo();

	// BM6 - 寻找第K大
	// findKth_Solution solu;
	// solu.demo();

	// BM7 - 数据流的中位数
	// StreamMid_Solution solu;
	// solu.demo();

	// BM8 - 表达式求值
	// ExpressionEvaluation_Solution solu;
	// solu.demo();
}

// 哈希测试函数
void haspTest()
{
	// BM2 - 数组中出现次数超过一半的数字
	MoreThanHalfNum_Solution solu;
	solu.demo();
}

int main()
{
	// 链表测试函数
	// fundLinkTest();

	// 二分查找测试函数
	// binarySearchTest();

	// 二叉树测试函数
	// binaryTreeTest();

	// 堆/栈/链表测试函数
	// heapStackQueueTest();

	// 哈希测试函数
	haspTest();

	return 0;
}