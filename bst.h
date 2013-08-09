#include <cstddef>
#include <iostream>
#ifndef BST_H
#define BST_H
#include <vector>

template<class Item>
class bstNode
{
    public:
    //constructor
    bstNode(const Item& init_data, bstNode* init_parent=NULL, bstNode* init_left=NULL, bstNode* init_right=NULL)
        {
            data_field = init_data;
            left_field = init_left;
            right_field = init_right;
            parent = init_parent;
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
    void remove(Item& targetData);
    int size();
    void traverse();
    
    //our private variables (we just have 3)
    private:
        Item data_field; //our data
        bstNode* left_field; //pointer to left child
        bstNode* right_field; //pointer to right child
        bstNode* parent;
};

//ALL OUR IMPLEMENTATIONS GO IN HERE-- NO .CPP FILE FOR BSTNODE BECUASE IT'S A TEMPLATE CLASS

template<class Item>
bool bstNode<Item>::find(Item& targetData)
{
    //check my self, check my children... if I find targetData I return true, else false
    if (targetData == data_field) return true;
    if (left_field != NULL && left_field->find(targetData)) return true;
    if (right_field != NULL && right_field->find(targetData)) return true;
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
    if (targetData <= data_field) {
        target_ptr = &left_field;
    } else {
        target_ptr = &right_field;
    }

    if (*target_ptr == NULL) {
        *target_ptr = new bstNode(targetData, this);
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
void bstNode<Item>::remove(Item& targetData)
{
    //go through and remove the item and remake the tree

    // have we found the data?
    if (data_field == targetData) {
 
        // if so, determine how to delete
     
        if (left_field == NULL && right_field == NULL) {
            // if no children, remove the link in the parent node
            if (parent != NULL ) {
                if (parent->left_field == this) { parent->left_field = NULL; }
                else if (parent->right_field == this) { parent->right_field = NULL; }
            }
            // if no parent node ... ???
        
        } else if (left_field != NULL && right_field != NULL) {
            // if two children, find the left-most descendant of the right child
            // and swap its value with this one, then remove that descendant
            bstNode* current_node = right_field;
            while (current_node->left_field != NULL) {
                // grab the left child
                current_node = current_node->left_field;
            }
            Item target_data = current_node->data_field;
            data_field = target_data;
            //right_field->remove(target_data);
            current_node->remove(target_data);
     
        } else {
            // if one child, essentially replace this node with child node
            bstNode* target;
            if (left_field != NULL) { target = left_field; }
            else if (right_field != NULL) { target = right_field; }

            // retain parent field, but copy rest of data
            this->data_field = target->data_field;
            this->left_field = target->left_field;
            this->right_field = target->right_field;
            
        }

        // finally, call the destructor on this node
        // this.~bstNode();
        
    // if not, check the left child if it exists
    } 
    else if (targetData <= data_field && left_field != NULL) { left_field->remove(targetData); }
        
    // and the right child if it exists
    else if (targetData > data_field && right_field != NULL) { right_field->remove(targetData); }
    
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
    int row = 0;
    vector<bstNode*> this_row;
    vector<bstNode*> next_row;
    this_row.push_back(this);
    while ( !this_row.empty() ) {
        cout << "R" << row << endl;
        while ( !this_row.empty() ) {
            bstNode* cur = this_row.front();
            cout << cur->data_field << endl;
            if (cur->left_field != NULL) next_row.push_back(cur->left_field);
            if (cur->right_field != NULL) next_row.push_back(cur->right_field);
            this_row.erase(this_row.begin());
        }
        this_row = next_row;
        next_row.clear();
        row ++;
        cout << "---------" << endl;
    }
}

#endif
