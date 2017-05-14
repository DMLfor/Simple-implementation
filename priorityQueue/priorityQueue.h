#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED
#include <vector>
using std:: cout;
using std:: vector;
template <class T>
class priorityQueue
{
private:
    vector<T> ptr;
    int comp;
public:
    priorityQueue(int mark = 0);   //mark为0时为小顶堆,1时为大顶堆
    ~priorityQueue() {}
    void Pop();
	size_t Size() { return ptr.size(); }
    bool Empty() {return ptr.size() == 0; }
    void Push(const T & element);
    T Front() { return ptr.front(); }
};

template <class T>
priorityQueue<T>:: priorityQueue(int mark)
{
	comp = mark;
}

template <class T>
void priorityQueue<T>:: Push(const T & element)
{
	size_t  i;
	ptr.push_back(element);
	if(Empty())
		ptr.push_back(element);
	else
		for(i = ptr.size(); i/2 && (comp ? (ptr[i/2-1] < element) : !(ptr[i/2-1] < element)); i >>= 1)
			ptr[i-1] = ptr[i/2-1];

	ptr[i-1] = element;
}

template <class T>
void priorityQueue<T>:: Pop()
{
	size_t i, child;
	T lastData;
	lastData = ptr.back();
	ptr.pop_back();
	for(i = 1; i*2<=ptr.size(); i = child)
	{
		child = i * 2;
		if(child != ptr.size() && (comp ? (ptr[child-1] < ptr[child]) : !(ptr[child-1] < ptr[child])))
			child ++;

		if(comp ? (lastData < ptr[child-1]) : !(lastData < ptr[child-1]))
			ptr[i-1] = ptr[child-1];
		else break;
	}
	ptr[i-1] = lastData;
}


#endif // PRIORITYQUEUE_H_INCLUDED
