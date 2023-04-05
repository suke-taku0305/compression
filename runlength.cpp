#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;

vector<pair<char, int>> encode(const string& str){
    int n = (int)str.size();
    vector<pair<char, int>> ret;
    
    for(int l=0; l<n; ){
        int r = l+1;
        for(; r<n && str[l] == str[r]; r++) {};
        ret.push_back({str[l], r-l});
        l=r;
    }
    return ret;
}

string decode(const vector<pair<char, int>> &code){
    string ret = "";
    for(auto p : code){
        for(int i=0; i<p.second; i++){
            ret.push_back(p.first);
        }
    }
    return ret;
}

int main(){
    string S;
    cin >> S;
    vector<pair<char, int>> vec;
    vec = encode(S);
    for(size_t i=0; i<vec.size(); ++i){
        cout << vec.at(i).first << vec.at(i).second;
    }
    cout << endl;
    string plane = decode(vec);
    cout << plane << endl;
    return 0;
}