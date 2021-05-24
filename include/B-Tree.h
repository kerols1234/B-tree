#ifndef BTREE_H
#define BTREE_H
#include <iostream>

using namespace std;

template <class T, int M>
class BTreeNode
{
    public:
        BTreeNode(T &x)
        {
            keyPosition = 1;
            keys[] = new T[keyPosition];
            keys[0] = &x;
            leaf = true;
        };
        void insertValue(T &x)
        {
            keyPosition++;
            T *key[] = new T[keyPosition];
            int j = 0;
            for(int i = 0; i < keyPosition; i++,j++)
            {
                if(i == j && x <= keys[j])
                {
                    key[i] = &x;
                    j--;
                }
                else
                {
                    key[i] = keys[j];
                }
            }
            keys = key;
        };
        bool leaf;
        int keyPosition;
        T *keys[];
        BTreeNode *pointers[M];
};

template <class t>
class BTree
{
    public:
        BTree(int maxx)
        {
            m = maxx;
            root = NULL;
        };
        ~BTree();
        void insertion(int value)
        {
            if(root == NULL)
            {
                 BTreeNode node(value);
                 root = node;
            }

        };
        void deletion(int value)
        {

        };
        BTreeNode* predecessor(BTreeNode *node, int value)
        {

        };

    protected:

    private:
        BTreeNode *root;
        int m;
};

#endif
