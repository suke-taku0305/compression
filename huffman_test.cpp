#include "huffman_test.hpp"
#include <memory>

string bin2string(const vector<bool> &b){
    string s;
    for(int i=0; i<b.size(); i++){
        if(b[i]) s+='1';
        else s+='0';
    }
    return s;
}

int main(){
    vector<int> f = {5, 3, 2, 1, 1};
    auto ht_root = shared_ptr<HuffmanTree>(make_huffman_tree(f));
    auto coder = HuffmanCoder(ht_root.get());

    for(int i=0; i<coder.term2node.size(); ++i){
        auto huffcode = bin2string(coder.term2node[i]->huffcode());
        cout << i << "\t"
            << coder.term2node[i]->freq << "\t"
            << huffcode
            << endl;
    }

    vector<int> s = {0, 1, 2, 0};
    vector<bool> s_comp = coder.encode(s);
    for(auto xi : s) cout << xi << " ";
    cout << endl;
    cout << bin2string(s_comp) << endl;

    auto s2 = coder.decode(s_comp);
    for(auto xi : s2) cout << xi << " ";
    cout << endl;

    return 0;
}