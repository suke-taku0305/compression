#ifndef _HUFFMAN_TEST
#define _HUFFMAN_TEST

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>

#include "binary_tree.hpp"

using namespace std;

struct HuffmanTree : public BinaryTree {
    int freq;
    int term_id;
    bool label;
    HuffmanTree() {};
    HuffmanTree(HuffmanTree *left, HuffmanTree *right)
     : BinaryTree(left, right), freq(left->freq+right->freq)
    {left->label = false; right->label = true;}
    ~HuffmanTree() {}
    string huffcode_as_string() const {
        if(this->parent == nullptr) return "";
        else if(label) return static_cast<HuffmanTree*>(this->parent)->huffcode_as_string() + "1";
        else           return static_cast<HuffmanTree*>(this->parent)->huffcode_as_string() + "0";
    }
    vector<bool> huffcode() const {
        string huffcode_str = huffcode_as_string();
        vector<bool> code; code.resize(huffcode_str.size());
        for(int i=0; i<code.size(); ++i){
            if(huffcode_str[i] == '0'){
                code[i] = false;
            }else{
                code[i] = true;
            }
            return code;
        }
    }
};

struct HuffmanCoder{
    HuffmanTree *root;
    vector<HuffmanTree*> term2node;
    vector<vector<bool> > term2code;
    HuffmanCoder(HuffmanTree *root_) : root(root_) {
        int nleaf = root->leaf_size();
        term2node.resize(nleaf, nullptr);
        term2node.resize(nleaf);
        run_leaf(root);

        for(int i=0; i<nleaf; ++i){
            term2code[i] = term2node[i]->huffcode();
        }
    }

    vector<bool> encode(const vector<int> &x) const {
        vector<bool> bitseq;
        for(int xi : x){
        for(bool bi : term2code[xi])
            bitseq.push_back(bi);
        }
        return bitseq;
    }

    vector<int> decode(const vector<bool> &code) const {
        vector<int> str;
        HuffmanTree *node = this->root;
        for(int i=0; i<code.size(); ++i){
            if(!code[i]){
                if(node->left==nullptr) throw "Invalid code";
                if(node->left->is_leaf()){
                    str.push_back(static_cast<HuffmanTree*>(node->left)->term_id);
                    node = this->root;
                }else{
                    node = static_cast<HuffmanTree*>(node->left);
                }
            }else{
                if(node->right==nullptr) throw "Invalid code";
                if(node->right->is_leaf()){
                    str.push_back(static_cast<HuffmanTree*>(node->right)->term_id);
                    node = this->root;
                }else{
                    node = static_cast<HuffmanTree*>(node->right);
                }
            }
        }
        return str;
    }

    private:
        void run_leaf(HuffmanTree *node){
            if(node->is_leaf()){
                term2node[node->term_id] = node;
            }else{
                if(node->left) run_leaf(static_cast<HuffmanTree*>(node->left));
                if(node->right) run_leaf(static_cast<HuffmanTree*>(node->right));
            }
        }
};

HuffmanTree* make_huffman_tree(const vector<int> &frequency){
    size_t n = frequency.size();

    auto comp = [](const HuffmanTree* a, const HuffmanTree* b){return a->freq < b->freq;};

    priority_queue<HuffmanTree*, vector<HuffmanTree*>, decltype(comp)> nodes(comp);

    for(int w=0; w<n; w++){
        auto node = new HuffmanTree;
        node->freq = frequency[w];
        node->term_id = w;
        nodes.push(node);
    }

    HuffmanTree *root;
    for(int i=0; i<n-1; ++i){
        auto n1 = nodes.top(); nodes.pop();
        auto n2 = nodes.top(); nodes.pop();
        root = new HuffmanTree(n1, n2);
        root->term_id = -1;
        nodes.push(root);
    }
    return root;
}

#endif