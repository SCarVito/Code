#include <stdio.h>

bool is_onright(int a, int b, int x, int y){
    return (long int)b * (long int)x >= (long int)a * (long int)(b - y);
}

int readNumber(){
    int number = 0;
    char ch = getchar();
	while ( ch < '0' || ch > '9' )
        ch = getchar();
	while ( ch >= '0' && ch <= '9' ) {
		number = number * 10 + ch - '0';
		ch = getchar();
	}
	return number;
}

int main(){
    int n,m;
    setvbuf(stdin, new char[1 << 18], _IOFBF, 1 << 18);
    setvbuf(stdout, new char[1 << 18], _IOFBF, 1 << 18);
    n = readNumber();
    m = readNumber();

    unsigned int *A = new unsigned int[n], *B = new unsigned int[n];
    for(int count = 0; count < n; ++count){
        A[count] = readNumber();
        B[count] = readNumber();
    }
    int * pos = new int[n];
    unsigned int x,y;
    for(int count = 0; count < m; ++count){
        x = readNumber();
        y = readNumber();
        if( is_onright(A[n-1], B[n-1], x, y) ){
            pos[count] = n;
        }
        else if(is_onright(A[0], B[0], x, y)){
            int low = 0, high = n-1, mid = (low+high) / 2;
            while( (low < high) && !( is_onright(A[mid], B[mid], x, y) && ( !is_onright(A[mid+1], B[mid+1], x, y)))   ){
                if( is_onright(A[mid], B[mid], x, y) && is_onright(A[mid+1], B[mid+1], x, y)) {
                    low=mid+1;
                } else {
                    high=mid-1;
                }
                mid=(low + high)>>1;
            }

            if(  is_onright(A[mid], B[mid], x, y) && ( !is_onright(A[mid+1], B[mid+1], x, y)) ){
                pos[count] = mid+1;
            }
            else{
                printf("error");
            }
        }
        else {
            pos[count] = 0;
        }
    }
    for(int count = 0; count < m; ++count){
        printf("%d\n", pos[count]);
    }
    return 0;
}
