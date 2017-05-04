#include <iostream>
#include <limits.h>
#include "priorityQueue.h"

using namespace std;

priorityQueue:: priorityQueue(int nums, int mark)
{
    flag = mark;
    ptr = new int[nums+1];
    queLim = nums;
    Size = 0;
    if(flag == 0)
        ptr[0] = INT_MIN;
    else ptr[0] = INT_MAX;
}
priorityQueue:: ~priorityQueue()
{
    delete [] ptr;
}

void priorityQueue::Insert(int num)   //上虑操作
{
    int i;
    if(IsFull())
    {
        cout<<"The PriorityQueue is Full!"<<endl;
    }
    else
    {
        for(i = ++Size; (flag ? (ptr[i/2] < num) : (ptr[i/2] > num)); i >>= 1)
        {
            ptr[i] = ptr[i/2];
        }
        ptr[i] = num;
    }
}

void priorityQueue :: Pop()
{
    int i, child;
    int lastData;
    if(Empty())
    {
        cout<<"The priorityQueue is empty!"<<endl;
    }
    lastData = ptr[Size -- ];
    for(i = 1; i*2<=Size; i = child)　　　　　　　//下虑操作
    {
        child = i * 2;
        if(child !=  Size && (flag? (ptr[child] < ptr[child+1]) : (ptr[child] > ptr[child+1])) )
            child ++;
        if(flag? (lastData <  ptr[child]) : (lastData > ptr[child]))
            ptr[i] = ptr[child];
        else break;
    }
    ptr[i] = lastData;
}

int priorityQueue:: Front() const
{
    if(Size == 0)
    {
        cout<<"The priorityQueue is empty!"<<endl;
    }
    else
    {
        return ptr[1];
    }
}
