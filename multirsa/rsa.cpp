#include "rsa.hpp"
#include <iostream>
#include <ctime>
#include <vector>
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

bool simple(int n){
    if(n<2) return false;
    if(n==2) return true;
    if(n%2 == 0) return false;

    for(int k = 3; k*k <= n; k+=2){
        if (n%k == 0){
            return false;
        }
    }

    return true;
}

vector<bool> eratosthenes( int n ){
    //vector's nature number
    vector<bool> result( n+1, true );

    result[0] = false;
    result[1] = false;
    for(int k=2; k<=n; k++ ){
        if(!result[k] ) continue;
        for(int mk = 2*k; mk <= n; mk += k){
            result[ mk ] = false;
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

bool fermat(int n, int trial ){
    srand((unsigned int )time( NULL ));

    if(n<2) return false;
    if(n==2) return true;

    for(int i = 0; i < trial; i++ ){
        int a = rand() % (n-2) + 2;
        if(gcd(a, n) != 1){
            return false;
        }
        if(powmod(a, n-1, n) != 1){
            return false;
        }
    }
    return true;
}

int exgcd( int a, int b ) {
    int x1 = 0, y1 = 1, r1 = b;
    int x2 = 1, y2 = 0, r2 = a;
    
    int x;
    int qq, rr;
    int xx, yy;
    
    while( true ) {
        qq = r1 / r2;
        rr = r1 % r2;

        xx = x1 - qq * x2;
        yy = y1 - qq * y2;
    
        if( rr == 0 ) {
            x = x2;
            break;
        }
    
        x1 = x2; y1 = y2; r1 = r2;
        x2 = xx; y2 = yy; r2 = rr;
    }

    while( x <= 0 ) {
        x += b;
    }

    return x;
}

