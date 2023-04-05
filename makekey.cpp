#include "rsa.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char *argv[]){
    //segmentation fault
    if( argc < 2 ){
        cout << "Please input N" << endl;
        exit(1);
    }

    int N = atoi(argv[1]);

    srand((unsigned int)time(NULL));

    vector<int> primeNum;
    int size = 0;

    for(int n=0; n<=N; n++){
        if(simple(n)){
            primeNum.push_back(n);
        }
    }
    size = primeNum.size();

    int p,q;
    p = primeNum[rand() % size];
    do {
        q = primeNum[rand() % size];
    }while( p == q );

    int n = p * q;

    int m = lcm( p-1, q-1 );

    int e = m;
    if( !(e & 1)) e++;

    int d;
    do {
        e += 2;
        while(gcd(e,m) != 1) e+=2;
        d = exgcd( e,m );
    }while(e == d);

    cout << "e: " << e << endl;
    cout << "d: " << d << endl;
    cout << "n: " << n << endl;

    return 0;
}