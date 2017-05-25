#include <bits/stdc++.h>
#include "ADT.hpp"

using namespace std;

int main()
{
    ADT tree;
    int a[] = {9, 5, 3, 2, 6, 4, 1, 10, 8, 7};
    for(int i = 0; i<10; i++)
    {
        tree.Change(tree.Insert(a[i], tree.Root()));
        cout<<tree.FindMax(tree.Root())->element<< " " << tree.FindMin(tree.Root())->element<<endl;
    }
    tree.print(tree.Root());
    cout<<'\n';
    tree.Change(tree.Delete(tree.FindMax(tree.Root())->element, tree.Root()));
    tree.print(tree.Root());
    cout<<'\n';
    tree.Change(tree.Delete(tree.FindMin(tree.Root())->element, tree.Root()));
    tree.print(tree.Root());
    cout<<'\n';

    tree.Change(tree.Delete(5, tree.Root()));
    tree.print(tree.Root());
    cout<<'\n';

    return 0;
}
