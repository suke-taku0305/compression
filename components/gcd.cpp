#include <iostream>
using namespace std;

int gcd( int a, int b ){
    //gcd(a,b) = gcd(b, a mod b)
    while(b > 0){
        int t = a%b;
        a = b;
        b = t;
    }
    return a;
}

int main( int argc , char *argv[]){
    //for segmentation fault
    if ( argc < 3 ){
        cout << "Please input (a,b)" << endl;
        exit(1);
    }
    int a = atoi( argv[1] );
    int b = atoi( argv[2] );

    int result = gcd(a, b);
    cout << "GCD(" << a << "," << b << ") = " << result << endl;
    return 0;
}