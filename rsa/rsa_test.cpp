#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <random>
using namespace std;


// 未完成(他のコードに変更)


random_device rd;
mt19937 gen(rd());

int random(int low, int high)
{
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

int modular_exp(int a, int b, int n){
    int res = 1;
    while(b != 0){
        if( b & 1 != 0){
            res = (res * a) % n;
        }
        a = (a*a) % n;
        b = b >> 1;
    }
    return res;
}

int gen_rand(int bit_length){
    vector<int> bits;
    for(int i=0; i<bit_length-2; i++){
        bits.push_back(random(0,1));
    }
    int ret = 1;
    for(int b=0; b<bits.size(); b++){
        ret = ret*2 + b;
    }
    return ret*2 + 1;
}

bool mr_primary_test(int n){
    if(n==1){
        return false;
    }
    if(n==2){
        return true;
    }
    if(n%2 == 0){
        return false;
    }
    int d = n-1;
    int s = 0;
    while(d%2 != 0){
        d /= 2;
        s += 1;
    }

    vector<int> rlst;
    for(int i=0; i<100; i++){
        rlst.push_back(random(1,n-1));
    }
    for(int a = 0; a<rlst.size(); a++){
        if(modular_exp(a, d, n) != 1){
            for(int rr = 0; rr < s; rr++){
                int pl = pow(2,rr) * d;
                bool flg = true;
                for(int p=0; p<pl; p++){
                    if(modular_exp(a, p, n) == 1){
                        flg = false;
                        break;
                    }
                    if(flg){
                        return false;
                    }
                }
            }
        }
        return true;
    }
}

int gen_prime(int bit){
    while(true){
        int ret = gen_rand(bit);
        if(mr_primary_test(ret)){
            break;
        }
        return ret;
    }
}

unsigned euclidean_gcd(unsigned a, unsigned b) {
    int x0 = 1;


    if(a < b) return euclidean_gcd(b, a);
    unsigned r;
    while ((r=a%b)) {
        a = b;
        b = r;
    }
    return b;
}
unsigned gen_d(){

}

int main(){
    int bit_length = 120;
    int p = gen_prime(bit_length);
    int q = gen_prime(bit_length);
    int e = gen_prime(bit_length);
    int d = gen_d();
}