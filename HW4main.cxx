#include <iostream>
#include "bst.h"
using namespace std;

int main()
{
    bstNode<int>* root=NULL;//make an initial root pointer
    int data; //data to be cin by user
    char command; //command to be cin by user
    while(true) //we keep letting user do stuff until they hit q
    { //all our commands (some take 2 cin some take 1)
        
        cout<<"enter i followed by number to insert"<<endl;
        cout<<"enter r followed by number to remove"<<endl;
        cout<<"enter f followed by number to find"<<endl;
        cout<<"enter s to see the size of the tree"<<endl;
        cout<<"enter t to print out the tree"<<endl;
        cout<<"enter q q to quit"<<endl;
        cin>>command;
        if (command=='i' || command=='r' || command=='f')
        {
            cin>>data;
        }
        switch(command) //case statement that runs through our commands
        {
            //I gave case i, case f, case t as an example of how we do stuff in main
            case 'i':
                if (root==NULL) //ALWAYS check the NULL case before dereferencing
                    root=new bstNode<int>(data);
                else
                    root->insert(data);
                root->print();
                cout << endl;
                break;
            case 'r':
            //fill this in
                if (root != NULL) root->remove(data);
                root->print();
                cout << endl;
                break;
            case 'f':
                cout<<"***f "<<data<<"***"<<endl;
                if(root->find(data))
                {
                    cout<<"found!"<<endl;
                }
                else
                {
                    cout<<"Not Found!"<<endl;
                }
                break;
            case 's':
            //fill this in
                root == NULL ? cout << 0 : cout << root->size() ;
                cout << endl;
                break;
            case 't':
                if(root!=NULL)
                    root->traverse();
                cout << endl;
                break;
            case 'q':
                return 0;
                break;
        }
    }
    return 0;
}
