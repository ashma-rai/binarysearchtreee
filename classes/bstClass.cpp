#include "bstClass.h"
bstClass::bstClass()
{
    //ctor
    tree=nullptr;

}

bstClass::~bstClass()
{
    //dtor
}

 void bstClass::insertElement(node* &root, int val)
    {
        //int tempdata;
        if(root == nullptr)
        {
            node *temp = new node;
            temp->data = val;
            root = temp;
            root->left = nullptr;
            root->right = nullptr;


            root->pos=tree->pos;

            cout<<"root>pos = "<<root->pos<<endl;
            returnVal(root->pos,counter,tree->prepos);
            tree->pos=0;
            counter=0;
            //arrayNodes[arrayIndex]=root->data;
            //arrayIndex++;


        }
        else
        {   tree->prepos=tree->pos;

            if(val < root->data)
            {
                if (counter==0) {
                        //prevpos

                        tree->pos=root->pos-400;
                }
                else { //temp->pos=tree->pos;//prevpos
                        tree->pos=root->pos-200/counter;}
                counter++;
                cout<<"tree>pos ="<<tree->pos<<endl;
                cout<<" traversed left"<<endl;
                insertElement(root->left, val);
            }
            else
            {
                if (counter==0) {
                        //temp->pos=0;
                        tree->pos=root->pos+400;}
                else{
                    //temp->pos=tree->pos;
                    tree->pos=root->pos+200/counter;}
                counter++;
                cout<<"tree>pos ="<<tree->pos<<endl;
                cout<<" traversed right "<<endl;
                insertElement(root->right, val);
            }

        }

    }
//traversals

  void bstClass:: preorder(node *root)
    {
        if(root != nullptr)
        {
            std::cout << root->data <<"  ";
            preorder(root->left);
            preorder(root->right);
        }
    }

    void bstClass::inorder(node *root)
    {
        if(root != nullptr)
        {
            preorder(root->left);
            std::cout << root->data <<"  ";
            preorder(root->right);
        }
    }

    void bstClass::postorder(node *root)
    {
        if(root != nullptr)
        {
            preorder(root->left);
            preorder(root->right);
            std::cout << root->data <<"  ";
        }
    }



    void bstClass::searchElement(node *root, int val)
    {
        if(root == nullptr)
        {   //dataPresent=false;
            std::cout<<val<<"  is not present\n";
        }
        else if(root->data == val)
        {    //tree->data=val;

            displaySearchedNode=true;
            std::cout<<val<<"  is present\n";

        }
        else
        {
            if(val < root->data)
                searchElement(root->left, val);
            else
                searchElement(root->right, val);
        }
    }
