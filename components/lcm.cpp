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

int lcm( int a, int b ){
    // a*b = gcd(a,b) * lcm(a,b)
    return ( a*b ) / gcd(a, b);
}

int main( int argc, char *argv[] ){
    // segmentation fault
    if( argc < 3 ){
        cout << "Please input (a,b)" << endl;
        exit(1);
    }

    //str to int
    int a = atoi( argv[1] );
    int b = atoi( argv[2] );

    int result = lcm(a,b);
    cout << "LCM(" << a << "," << b << ") = " << result << endl;

    return 0;
}