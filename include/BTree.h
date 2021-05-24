#ifndef BTREE_H
#define BTREE_H
#include <iostream>

using namespace std;

template <class T, int M>
class BTreeNode
{
public:
    BTreeNode()
    {
        keyPosition = 0;
        children = new BTreeNode*[M+1];
        for(int i = 0; i < M+1; i++)
        {
            children[i] = NULL;
        }
        keys = new T[keyPosition];
        parent = NULL;
    };

    BTreeNode(T &x)
    {
        keyPosition = 1;
        children = new BTreeNode*[M+1];
        for(int i = 0; i < M+1; i++)
        {
            children[i] = NULL;
        }
        keys = new T[keyPosition];
        keys[0] = x;
        parent = NULL;
    };

    void insertValueToLeave(T &x)
    {
        keyPosition++;
        T *key = new T[keyPosition];
        int j = 0, i = 0,p = keyPosition-1;
        for(; j < keyPosition-1; i++,j++)
        {
            if(i == j && x <= keys[j])
            {
                p = i;
                j--;
            }
            else
                key[i] = keys[j];
        }
        key[p] = x;
        keys = key;
    };

    void split()
    {
        int x = keyPosition/2,i,j;
        BTreeNode<T,M> *newNode = new BTreeNode<T,M>();
        T temp= this->keys[x];

        newNode->keys = new T[keyPosition-x+1];
        for(i = 0,j = x+1; j < keyPosition; i++,j++)
        {
            newNode->keys[i] = this->keys[j];
            newNode->keyPosition++;
            newNode->children[i] = this->children[j];
            this->children[j] = NULL;
        }
        newNode->children[i] = this->children[j];
        this->children[j] = NULL;

        T* k = new T[x];
        for(int i = 0; i < x; i++)
            k[i] = this->keys[i];
        this->keys = k;
        this->keyPosition = x;

        if(this->parent == NULL)
        {
            BTreeNode<T,M> *root = new BTreeNode<T,M>(temp);
            root->children[0] = this;
            root->children[1] = newNode;
            newNode->parent = root;
            this->parent = root;
        }
        else
        {
            int i = 0;
            T v;

            for(; i < this->parent->keyPosition; i++)
            {
                if(temp < this->parent->keys[i])
                    break;
            }

            this->parent->insertValueToLeave(temp);

            BTreeNode<T,M> * s = this->parent->children[i+1];
            BTreeNode<T,M> * d = NULL;
            this->parent->children[i+1] = newNode;
            newNode->parent = this->parent;
            for(int j = i+2; j < M+1; j++)
            {
                d = this->parent->children[j];
                this->parent->children[j] = s;
                s = d;
            }
        }
    };

    BTreeNode* findNextNode(T value)
    {
        int  i = 0;
        for(; i < keyPosition; i++)
        {
            if(keys[i] >= value)
                break;
        }
        return children[i];

    };

    void traverse(string x = "  ")
    {
        int i;
        cout<<x;
        for (i = 0; i < keyPosition; i++)
        {
            x += " ";
            cout << " " << (keys[i]);
        }
        cout<<endl;
        for (i = 0; i < keyPosition+1; i++)
        {
            if(children[i] == NULL)
                break;
            children[i]->traverse(x + " ");
        }
    };

    int keyPosition;
    T *keys;
    BTreeNode **children;
    BTreeNode *parent;

};

template <class t, int m>
class BTree
{
public:
    BTree()
    {
        root = NULL;
    };
    ~BTree() {};
    void Insert(t value)
    {
        if(root == NULL)
        {
            BTreeNode<t,m> *node = new BTreeNode<t,m>(value);
            root = node;
        }
        else
        {
            BTreeNode<t,m> *current = root;
            while(current->children[0] != NULL)
                current = current->findNextNode(value);
            current->insertValueToLeave(value);

            while(current->keyPosition == m)
            {
                current->split();
                if(current == root)
                    root = current->parent;
                current = current->parent;
            }
        }

    };
    void Print()
    {
        root->traverse();
        cout<<endl;
    }
private:
    BTreeNode<t,m> *root;
};

#endif

