#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED
#include <iostream>
class priorityQueue
{
private:
    int *ptr;
    int Size;
    int queLim;
    int flag;
public:
    priorityQueue(int nums, int mark);
    ~priorityQueue();
    void Pop();
    bool IsFull(){ return Size == queLim; };
    bool Empty() {return Size == 0; };
    void Insert(int num);
    int Front() const;
};

#endif // PRIORITYQUEUE_H_INCLUDED
