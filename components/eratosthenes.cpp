#include <iostream>
#include <vector>
using namespace std;

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

int main(int argc, char *argv[] ){
    if(argc<2){
        cout << "Please input N" << endl;
        exit(1);
    }
    int N = atoi(argv[1]);
    //under N's result
    vector<bool> result = eratosthenes(N);
    for(int n = 0; n<=N; n++){
        if( result[n] ) {
            cout << n << " ";
        }
    }
    cout << endl;

    return 0;
}