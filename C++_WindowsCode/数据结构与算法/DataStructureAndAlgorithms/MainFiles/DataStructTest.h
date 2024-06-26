#pragma once
#include <iostream>
#include "../DataStructure/DataStruct_Array/DynamicArray.h"
#include "../DataStructure/DataStruct_Array/DynamicArrayAdv.h"
#include "../DataStructure/DataStruct_LinkList/SingleLinkList.h"
#include "../DataStructure/DataStruct_LinkList/DoubleLinkList.h"
#include "../DataStructure/DataStruct_Stack/SequenceStack.h"
#include "../DataStructure/DataStruct_Stack/LinkStack.h"
#include "../DataStructure/DataStruct_Queue/SequenceQueue.h"
#include "../DataStructure/DataStruct_Queue/MonotonicQueue.h"
#include "../DataStructure/DataStruct_Queue/PriorityQueue.h"
#include "../DataStructure/DataStruct_Tree/BinaryTree.h"
using std::cout;
using std::endl;

/*���ݽṹ����																**/
void dataStructTest();

/*��̬�������																**/
void funcDynamicArrayTest();

/*�Ľ��涯̬�������														**/
void funcDynamicArrayAdvTest();

/*������������																**/
void funcSingleLinkListTest();

/*˫����������																**/
void funcDoubleLinkListTest();

/*˳��ջ����																**/
void funcSequenceStackTest();

/*��ʽջ����																**/
void funcLinkStackTest();

/*˳����в���																**/
void funcSequenceQueueTest();

/*�������в���																**/
void funcMonotonicQueueTest();

/*���ȶ��в���																**/
void funcPriorityQueueTest();

/*����������																**/
void funcBinaryTreeTest();