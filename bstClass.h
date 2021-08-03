#ifndef BSTCLASS_H
#define BSTCLASS_H
#include<iostream>
//#include"drawing.h"
using namespace std;
extern void returnVal(int val,int counter,int prevPos);
extern bool displaySearchedNode;
//extern int searchedIndex;
//extern int arrayIndex;
//extern arrayNodeStruct arrayNode[100];
class bstClass
{
    public:
int counter=0;
struct node
{
    int data;
    node *left;
    node *right;
    int pos=0;
    int prepos=0;
};
node *tree;
//node *temp = new node;
//tree.data=0;
        bstClass();
        virtual ~bstClass();

        void insertElement(node*&, int);
        void preorder(node*);
        void inorder(node*);
        void postorder(node*);
        void searchElement(node*, int);
};

#endif // BSTCLASS_H
