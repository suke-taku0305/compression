#include <iostream>
#include "rsa.hpp"
using namespace std;

int main(void){
    int C, d, n;
    cout << "C: "; cin >> C;
    cout << "d: "; cin >> d;
    cout << "n: "; cin >> n;
    cout << C << " ^ " << d << " mod " << n << " = M = " << powmod( C, d, n ) << endl;
    return 0;
}