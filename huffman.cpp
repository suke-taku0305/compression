#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;

void get_distribution(string S, map<char, int> &dist){
    for (int i=0; i < (int) S.length(); i++){
        dist[S[i]]++;
    }
}

void initialize_huffman_tree(map<char, int> &dist, vector<tuple<int, vector<int> ,string > > &T){
    int i = 0;
    vector<int> temp = {};
    for (auto itr: dist){
        T[i] = make_tuple(dist[itr.first], temp, "");
        i++;
    }
}

void initialize_priority_queue(map<char, int> &dist, priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > &pque){
    int i = 0;
    for (auto itr: dist){
        pque.push(make_pair(itr.second, i));
        i++;
    }
}

void make_huffman_tree(map<char, int> &dist, vector<tuple<int, vector<int>, string> > &T, priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > & pque){
    for(int i=(int) dist.size(); i<2*dist.size()-1; i++){
        pair<int, int> temp1 = pque.top();
        pque.pop();
        pair<int, int> temp2 = pque.top();
        pque.pop();
        pair<int, int> temp3 = make_pair(temp1.first+temp2.first, i);
        pque.push(temp3);
        vector<int> temp4 = {temp1.second, temp2.second};
        T[i] = make_tuple(temp3.first, temp4, "");
    }
}

void huffman_tree_dfs(vector<tuple<int, vector<int>, string > > &T, int v){
    vector<int> temp1 = {};
    if (get<1>(T[v]) != temp1){
        for(int i=0; i < 2;i++){
            string temp2 = get<2>(T[v]) + (char) (i+'0');
            int idx = get<1>(T[v])[i];
            T[idx] = make_tuple(get<0>(T[idx]), get<1>(T[idx]), temp2);
            huffman_tree_dfs(T, idx);
        }
    }
}

int main(){
    //入力
    string S;
    cin >> S;


    //① 文字の出現頻度を求める
    map<char, int> dist;
    get_distribution(S, dist);
    int N = dist.size();

    //種類数が1の場合はダミーの文字を入れる必要がある
    bool dummy_flag = false;
    if (N == 1){
        dummy_flag = true;
        N++;
        char dummy = (char) (S[0]+1);
        dist[dummy] = 0;
    }



    //②.① 各文字に対応するノードを1つずつ作る
    vector<tuple<int, vector<int>, string> > T(2*N-1);
    initialize_huffman_tree(dist, T);


    //②.② 親を持たないノードのうち、出現頻度が小さい2つのノードを選ぶ
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pque;
    initialize_priority_queue(dist, pque);


    //②.③ その2つの出現頻度を足し合わせたノードを新たに作る
    //②.④ 新たなノードをその2つのノードの親とする
    //②.⑤ 2-4の手順を全てのノードがつながれるまで繰り返す
    make_huffman_tree(dist, T, pque);


    //③ ハフマン木の各エッジに0と1を当てはめていく
    //④ ハフマン木の根から文字までのノードを辿ってできたビット列が符号語となる
    huffman_tree_dfs(T, 2*N-2);


    //出力
    if (dummy_flag) N--;

    cout << N << endl;

    map<char, string> codeword;//符号語
    int i = 0;
    for (auto itr : dist){
        if (i < N){
            cout << itr.first << " "  << get<2>(T[i]) << endl;
            codeword[itr.first] = get<2>(T[i]);
            i++;
        }
    }

    for (int i = 0; i < (int) S.length(); i++){
        cout << codeword[S[i]];
    }
    cout << endl;

    return 0;
}