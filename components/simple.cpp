#include <iostream>
using namespace std;

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

int main( int argc, char *argv[] ){
    //segmentation fault
    if(argc < 2){
        cout << "Please input N" << endl;
        exit(1);
    }

    int N = atoi(argv[1]);

    for(int n = 0; n<=N; n++){
        if(simple(n)){
            cout << n << " ";
        }
    }
    cout << endl;

    return 0;
}