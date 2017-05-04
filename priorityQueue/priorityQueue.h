#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED
using std:: cout;
template <class T>
class priorityQueue
{
private:
    T *ptr;
    int Size;
    int queLim;
    int flag;
	enum {maxn = 10000};
public:
    priorityQueue(int nums, int mark = 0);   //mark为0时为小顶堆,1时为大顶堆
    ~priorityQueue();
    void Pop();
    bool IsFull(){ return Size == queLim; };
    bool Empty() {return Size == 0; };
    void Insert(const T & element);
    T Front();
};

template <class T>
priorityQueue<T>:: priorityQueue(int nums, int mark)
{
	flag = mark;
	ptr = new T[nums+1];
	Size = 0;
	queLim = nums;
}

template <class T>
void priorityQueue<T>:: Insert(const T & element)
{
	int i;
	if(IsFull())
		cout << "The PirorityQueue is full.\n";
	else
	{
		if(Size == 0)
			i = ++ Size;
		else
		for(i = ++Size;i/2!=0 && (flag ? (ptr[i/2] < element) : !(ptr[i/2] < element)); i >>= 1)
			ptr[i] = ptr[i/2];

		ptr[i] = element;
	}
}

template <class T>
void priorityQueue<T>:: Pop()
{
	int i, child;
	T lastData;
	if(Empty())
	{
		cout << "The priorityQueue is empty.\n";
	}
	lastData = ptr[Size --];
	for(i = 1; i*2<=Size; i = child)
	{
		child = i * 2;
		if(child != Size && (flag ? (ptr[child] < ptr[child+1]) : !(ptr[child] < ptr[child+1])))
			child ++;

		if(flag ? (lastData < ptr[child]) : !(lastData < ptr[child]))
			ptr[i] = ptr[child];
		else break;
	}
	ptr[i] = lastData;
}

template<class T>
T priorityQueue<T>:: Front()
{
	if(Empty())
		cout << "The priorityQueue is empty.\n";
	else
	{
		return ptr[1];
	}
}

template<class T>
priorityQueue<T>:: ~priorityQueue()
{
	delete [] ptr;
}
#endif // PRIORITYQUEUE_H_INCLUDED
