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

    //今回はe=65537とする
    int e = 65537;

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

    int p1,q1;
    p1 = primeNum[rand() % size];
    do {
        q1 = primeNum[rand() % size];
    }while( p1 == q1 );

    int n1 = p1 * q1;

    // int m = lcm( p1-1, q1-1 );

    // int e = m;
    // if( !(e & 1)) e++;

    // int d;
    // do {
    //     e += 2;
    //     while(gcd(e,m) != 1) e+=2;
    //     d = exgcd( e,m );
    // }while(e == d);

    int d1 = exgcd( e, (p1-1)*(q1-1) );

    int p2,q2;
    p2 = primeNum[rand() % size];
    do {
        q2 = primeNum[rand() % size];
    }while( p2 == q2 );

    int n2 = p2 * q2;

    int d2 = exgcd( e, (p2-1)*(q2-1) );

    int multiply = n1*n2;

    cout << "make key faze" << endl;

    cout << "e: " << e << endl;
    cout << "d1: " << d1 << endl;
    cout << "n1: " << n1 << endl;
    cout << "d2: " << d2 << endl;
    cout << "n2: " << n2 << endl;
    cout << "multiply: " << multiply << endl;

    cout << "encryption faze for both" << endl;

    int M;
    cout << "please enter plaintext M: "; cin >> M;
    cout << M << "^" << e << " mod " << multiply << " = C = " << powmod(M, e, multiply) << endl;

    cout << "decryption faze by first client" << endl;
    int C = powmod(M, e, multiply);

    cout << C << " ^ " << d1 << " mod " << n1 << " = M = " << powmod( C, d1, n1 ) << endl;

    cout << "decryption faze by second client" << endl;

    cout << C << " ^ " << d2 << " mod " << n2 << " = M = " << powmod( C, d2, n2 ) << endl;




    cout << "encryption faze for first only" << endl;

     cout << M << "^" << e << " mod " << n1 << " = C = " << powmod(M, e, n1) << endl;

    cout << "decryption faze by first client" << endl;
    int C2 = powmod(M, e, n1);

    cout << C2 << " ^ " << d1 << " mod " << n1 << " = M = " << powmod( C2, d1, n1 ) << endl;

    cout << "decryption faze by second client" << endl;

    cout << C2 << " ^ " << d2 << " mod " << n2 << " = M = " << powmod( C2, d2, n2 ) << endl;

    return 0;
}