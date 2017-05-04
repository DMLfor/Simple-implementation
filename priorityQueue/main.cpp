#include <iostream>
#include "priorityQueue.h"
#include <string>
using namespace std;
struct node
{
	string name;
	int val;
	node(){}
	node(string __name, int __val)
	{
		name = __name;
		val = __val;
	}
	bool operator < (const node & rhs) const
	{
		return val < rhs.val;
	}
};
int main()
{
   node nums[5] = {node("asd", 1), node("dasdasd", 2), node("iiii", -1), node("zzzz", 1), node("asd", 8)};
   	priorityQueue<node> que(10, 1);
    for(int i = 0; i<5; i++)
    {
        que.Insert(nums[i]);
    }
    while(!que.Empty())
    {
		node x  = que.Front();
        cout << x.name<<' '<<x.val<<'\n';
        que.Pop();
    }
    return 0;
}
