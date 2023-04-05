#ifndef _BINARY_TREE
#define _BINARY_TREE

#include <iostream>

struct BinaryTree{
    int id;
    BinaryTree *left;
    BinaryTree *right;
    BinaryTree *parent;
    BinaryTree() : left(nullptr), right(nullptr), parent(nullptr) {}
    BinaryTree(BinaryTree *_left, BinaryTree *_right) : left(_left), right(_right), parent(nullptr) {
        left->parent = this;
        right->parent = this;
    }
    ~BinaryTree(){
        delete left; delete right;
    }
    BinaryTree* add_left(){
        if(left != nullptr){
            left = new BinaryTree;
            left->parent = this;
        }
        return left;
    }
    BinaryTree* add_right(){
        if(right != nullptr){
            right = new BinaryTree;
            right->parent = this;
        }
        return right;
    }
    size_t size() const {
        size_t n = 1;
        if(left) n += left->size();
        if(right) n += right->size();
        return n;
    }
    bool is_leaf() const {
        return (left==nullptr) && (right==nullptr);
    }
    size_t leaf_size() const {
        size_t n = 0;
        if(this->is_leaf()) return 1;
        else{
            if(left) n += left->leaf_size();
            if(right) n += right->leaf_size();
        }
        return n;
    }
};

#endif