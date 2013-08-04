#include <cstddef>
#include <iostream>
#ifndef BST_H
#define BST_H

template<class Item>
class bstNode
{
    public:
    //constructor
    bstNode(const Item& init_data, bstNode* init_left=NULL, bstNode* init_right=NULL)
        {
            data_field = init_data;
            left_field = init_left;
            right_field = init_right;
        }
    //helper functions if you need them ..
    //I think I haven't used any of them so far    
    //Item& get_data() {return data_field;}
    // void set_data(Item& target) {data_field=target;}
    // bstNode*& get_left() {return left_field;}
    // bstNode*& get_right() {return right_field;}

    void print();
    
    //FUNCTIONS YOU IMPLEMENT BELOW
    bool find(Item& targetData);
    void insert(Item& targetData);
    void remove(Item& targetData, bstNode* parent = NULL);
    int size();
    void traverse();
    
    //our private variables (we just have 3)
    private:
        Item data_field; //our data
        bstNode* left_field; //pointer to left child
        bstNode* right_field; //pointer to right child
};

//ALL OUR IMPLEMENTATIONS GO IN HERE-- NO .CPP FILE FOR BSTNODE BECUASE IT'S A TEMPLATE CLASS

template<class Item>
bool bstNode<Item>::find(Item& targetData)
{
    //check my self, check my children... if I find targetData I return true, else false
    if (targetData == data_field) return true;
    if (left_field != NULL) return left_field->find(targetData);
    if (right_field != NULL) return right_field->find(targetData);
    return false;
}

template<class Item>
void bstNode<Item>::insert(Item& targetData)
{
    //go through and find the correct place to insert a new node
    //with this data, remember that you print out the tree in 
    //that specific format after you insert!
    
    // smaller data on the left, greater or equal data on the right
    bstNode** target_ptr;
    if (targetData < data_field) {
        target_ptr = &left_field;
    } else {
        target_ptr = &right_field;
    }

    if (*target_ptr == NULL) {
        *target_ptr = new bstNode(targetData);
    } else {
        (*target_ptr)->insert(targetData);
    }
}

template<class Item>
void bstNode<Item>::traverse()
{
    //print out the sequence of data using IN ORDER traversal

    // in-order traversal: left, self, right
    if (left_field != NULL) left_field->traverse() ;

    // print self
    std::cout << data_field << " ";

    if (right_field != NULL) right_field->traverse();
}

template<class Item>
void bstNode<Item>::remove(Item& targetData, bstNode* parent)
{
    //go through and remove the item and remake the tree
    using namespace std;
    bool debug = true;

    // have we found the data?
    if (data_field == targetData) {
        if (debug) cout << "found the data!" << endl;
 
        // if so, determine how to delete
     
        if (left_field == NULL && right_field == NULL) {
            if (debug) cout << "no children found!" << endl;
            // if no children, remove the link in the parent node
            if (parent != NULL ) {
                if (parent->left_field == this) { parent->left_field = NULL; }
                else if (parent->right_field == this) { parent->right_field = NULL; }
            }
        
        } else if (left_field != NULL && right_field != NULL) {
            if (debug) cout << "two children found!" << endl;
            // if two children, find the left-most descendant of the right child
            // and swap its value with this one, then remove that descendant
            bstNode* current_node = right_field;
            while (current_node->left_field != NULL) {
                // grab the left child
                current_node = current_node->left_field;
            }
            Item target_data = current_node->data_field;
            data_field = target_data;
            right_field->remove(target_data, this);
     
        } else {
            // if one child, make the parent point to the child
            if (debug) cout << "one children found!" << endl;
            if (parent != NULL ) {
                // find our single child
                bstNode* target;
                if (left_field != NULL) { target = left_field; }
                else if (right_field != NULL) { target = right_field; }
                // make the parent point to the child instead of us
                if (parent->left_field == this) { parent->left_field = target; }
                else if (parent->right_field == this) { parent->right_field = target; }
            } 
        }

        // finally, call the destructor on this node
        
    } else {
        // if not, check the left child if it exists
        if (left_field != NULL) left_field->remove(targetData, this);
     
        // and the right child if it exists
        if (right_field != NULL) right_field->remove(targetData, this);
    }
}

template<class Item>
int bstNode<Item>::size()
{
    //go through and count the number of nodes in this
    int result = 1;
    if (left_field != NULL) result += left_field->size();
    if (right_field != NULL) result += right_field->size();
    return result;
}

template<class Item>
void bstNode<Item>::print() {
    using namespace std;
    cout << "/";
    if (left_field != NULL) left_field->print();
    cout << " | " << data_field << " | ";
    if (right_field != NULL) right_field->print();
    cout << "\\";
}

#endif
