#ifndef MYQUEUE_H_INCLUDE
#define MYQUEUE_H_INCLUDE

template <class Item>
class myqueue
{
private:
	class Node
	{
	public:
		Item element;
		Node *Next;
		Node(const Item & rhs): element(rhs), Next(0){}
	};
	Node *first;
	Node *last;
	int nums;
public:
	myqueue();
	~myqueue();
	bool empty() const { return nums == 0; }
	int size() const { return nums; }
	void push (const Item & rhs);
	void pop();
	Item front() const ;
	Item & front();

};

template <class Item>
myqueue<Item>:: myqueue()
{
	nums = 0;
	first = 0;
	last = 0;
}

template <class Item>
myqueue<Item>:: ~myqueue()
{
	Node *temp;
	while(first)
	{
		temp = first;
		first = first->Next;
		delete temp;
	}
}

template <class Item>
void myqueue<Item>:: push(const Item & rhs)
{
	Node *ptr = new Node(rhs);
	if(empty())
		first = ptr;
	else last->Next = ptr;
	last = ptr;
	++ nums;
}

template <class Item>
void myqueue<Item>:: pop()
{
	if(empty())
		return ;

	-- nums;
	Node *temp = first;
	first = first->Next;
	delete temp;
}

template <class Item>
Item & myqueue<Item>:: front()
{
	return first->element;
}

template <class Item>
Item myqueue<Item>:: front() const
{
	return first->element;
}
#endif


