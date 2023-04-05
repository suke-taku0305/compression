#include <iostream>
#include <ctime>
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

int main(int argc, char *argv[]){
    if(argc < 3){
        cout << "Please input (N, trial)" << endl;
        exit(1);
    }

    int N = atoi(argv[1]);
    int trial = atoi(argv[2]);

    for(int n = 0; n <= N; n++){
        if(fermat(n, trial)){
            cout << n << " ";
        }
    }
    cout << endl;

    return 0;
}