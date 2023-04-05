#include <iostream>
#include "rsa.hpp"
using namespace std;

int main(void){
    int M, e, n;
    cout << "M: "; cin >> M;
    cout << "e: "; cin >> e;
    cout << "n: "; cin >> n;
    cout << M << "^" << e << " mod " << n << " = C = " << powmod(M, e, n) << endl;
    return 0;
}