#include <iostream>
using namespace std;

void exgcd( int a, int b, int *px, int *py ) {
    int x1 = 0, y1 = 1, r1 = b;
    int x2 = 1, y2 = 0, r2 = a;
    
    int x, y;
    int qq, rr;
    int xx, yy;
    
    while( true ) {
        qq = r1 / r2;
        rr = r1 % r2;

        xx = x1 - qq * x2;
        yy = y1 - qq * y2;
    
        if( rr == 0 ) {
            x = x2;
            y = y2;
            break;
        }
    
        x1 = x2; y1 = y2; r1 = r2;
        x2 = xx; y2 = yy; r2 = rr;
    }

    while( x <= 0 ) {
        x += b;
        y -= a;
    }

    *px = x;
    *py = y;
}


int main( int argc, char *argv[] ) {
    if( argc < 3 ) {
        cout << "Please input (a,b)" << endl;
        exit( 1 );
    }
    int a = atoi( argv[ 1 ] );
    int b = atoi( argv[ 2 ] );

    int px, py;
    exgcd( a, b, &px, &py );
    cout << a << "x + " << b << "y = 1 -> (x,y) = (" << px << "," << py << ")" << endl;

    return 0;
}