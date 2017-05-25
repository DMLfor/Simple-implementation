#pragma once
#include <iostream>
using std::cout;
class ADT
{
private:
    class Node
    {
    public:
        int element;
        Node *left, *right;
        Node(int __element): element(__element), left(nullptr), right(nullptr) {}
    };
    Node *root;
public:
    typedef Node* Position;
    typedef Node* SearchTree;
    void print(SearchTree T)
    {
        if(T == nullptr)
            return ;
        if(T->left != nullptr)
            print(T->left);
	cout<<T->element<<'\n';
        if(T->right != nullptr)
            print(T->right);
    }
    ADT()
    {
        root = nullptr;
    }

    void Free(SearchTree T)
    {
        if(T->left != nullptr)
            Free(T->left);
        if(T->right != nullptr)
            Free(T->right);
        delete T;
    }

    ~ADT()
    {
        Free(root);
    }
    void Change(SearchTree T)
    {
        root = T;
    }
    SearchTree Root()
    {
        return root;
    }

    Position Find(const int & x, SearchTree  T)
    {
        if(T == nullptr)
            return nullptr;
        if(T->element > x)
            return Find(x, T->left);
        else if(T->element == x)
            return T;
        else return Find(x, T->right);
    }
    Position FindMin(SearchTree  T)
    {
        if(T == nullptr)
            return nullptr;
        if(T->left == nullptr)
            return T;
        else return FindMin(T->left);
    }
    Position FindMax(SearchTree  T)
    {
        if(T == nullptr)
            return nullptr;
        if(T->right == nullptr)
            return T;
        else return FindMax(T->right);
    }
    SearchTree Insert(const int & x, SearchTree T)
    {
        if(T == nullptr)
        {
            T = new Node(x);
        }
        else if(T->element <= x)
            T->right = Insert(x, T->right);
        else T->left = Insert(x, T->left);
        return T;
    }
    SearchTree Delete(const int & x, SearchTree T)
    {
        if(T == nullptr)
            return nullptr;
        else if(x > T->element)
            T->right =  Delete(x, T->right);
        else if(x < T->element)
            T->left = Delete(x, T->left);
        else if(T->left != nullptr && T->right != nullptr)
        {
            Position tmp = FindMin(T->right);
            T->element = tmp->element;
            T->right = Delete(T->element, T->right);
        }
        else
        {
            Position tmp = T;
            if(T->left == nullptr)
                T = T->right;
            else if(T->right == nullptr)
                T = T->left;
            free(tmp);
        }
        return T;
    }
};
