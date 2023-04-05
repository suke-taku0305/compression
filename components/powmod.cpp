#include <iostream>
using namespace std;

long long powmod( long long b, long long e, long long m) { 
    long long result = 1;

    //if pow=0 then result
    if (e == 0) return result;

    while( e > 0 ){
        if(e & 1){
            e--;
            result = result * b % m;
        }
        else{
            e >>= 1;
            b = b * b % m;
        }
    }

    return result;

}

int main ( int argc, char *argv[] ){
    // for segmentation fault
    if (argc < 4){
        cout << "Please input (b, e, m)" << endl;
        exit(1); 
    }

    //str to int
    int b = atoi( argv[1] );
    int e = atoi( argv[2] );
    int m = atoi( argv[3] );

    long long result = powmod( b, e, m );

    cout << b << " ^ " << e << " mod " << m << " = " << result << endl;

    return 0;
}