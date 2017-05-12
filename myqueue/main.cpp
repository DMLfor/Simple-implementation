#include <iostream>
#include "myqueue.h"

using std:: cout;
using std:: cin;
using std:: string;
int main()
{
	myqueue<string> q;
	string str;
	for(int i = 0; i<5; i++)
	{
		cin>>str;
		q.push(str);
		cout<<q.size()<<'\n';

	}

	while(!q.empty())
	{
		cout<<q.front()<<'\n';
		q.pop();
	}
	return 0;
}
