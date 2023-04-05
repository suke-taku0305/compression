#include <iostream>
#include <ctime>
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

bool rabin(int n){
    srand(( unsigned int )time(NULL));

    if( n<2 ) return false;
    if( n==2 ) return true;
    if(!(n & 1)) return false;

    int k = 0;
    int m = n-1;
    while( !(m&1)){
        m >>=1;
        k++;
    }

    int a = rand() % (n-2) + 2;
    
    long long y = powmod( a, m, n );
    if( y==1 || y == n-1 ){
        return true;
    }

    int i = 0;
    while( i<k ){
        y = powmod( y, 2, n );
        if( y == n-1 ) return true;
        if( y == 1 ) return false;
        i++; 
    }

    return false;
}

int main( int argc, char *argv[]){
    if ( argc < 2 ) {
        cout << "Please input n" << endl;
        exit(1);
    }

    int N = atoi(argv[1]);
    for(int n = 0; n<=N; n++){
        if(rabin(n)){
            cout << n << " ";
        }
    }
    cout << endl;

    return 0;
}