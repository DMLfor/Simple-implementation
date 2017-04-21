#include <iostream>
#include "priorityQueue.h"
using namespace std;

int main()
{
    int nums[10] = {1, 5, 3, 6, 2, 7, 8, 0, 9, 4};
    priorityQueue que(10, 0);
    for(int i = 0; i<10; i++)
    {
        que.Insert(nums[i]);
    }
    while(!que.Empty())
    {
        printf("%d\n", que.Front());
        que.Pop();
    }
    return 0;
}
