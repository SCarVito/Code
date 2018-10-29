#include <stdio.h>


const int SZ = 1 << 20;
struct fastio {   //fast io
	char inbuf[SZ];
	char outbuf[SZ];
	fastio() {
		setvbuf(stdin, inbuf, _IOFBF, SZ);
		setvbuf(stdout, outbuf, _IOFBF, SZ);
	}
}io;

struct Rlist{
    int id;
    Rlist* last;
    Rlist* next;
};

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
    int n, m, count=2;
    n = readNumber();
    m = readNumber();
    //scanf("%d %d", &n, &m);
    if(n==1){
        int num = readNumber();
        printf("%d", num);
        return 0;
    }
    struct Rlist * seq = new Rlist[n];

    seq[0].id = readNumber();
    seq[1].id = readNumber();
    //scanf("%d %d", &seq[0].id, &seq[1].id);
    seq[0].last = seq[0].next = &seq[1];
    seq[1].last = seq[1].next = &seq[0];
    Rlist* cursor = &seq[1];

    for(int i=2; i<n; i++){
        int temp = (m % count++);
        //int temp = m;
        while(temp--){
            cursor = cursor->next;
        }
        seq[i].id = readNumber();
//        scanf("%d", &seq[i].id);
        seq[i].last = cursor->last;
        cursor->last->next = &seq[i];
        seq[i].next = cursor;
        cursor->last = &seq[i];
        cursor = &seq[i];
    }

    for(int i=0; i<n; i++){
        printf("%d ", cursor->id);
        cursor = cursor->last;
    }
    delete[] seq;
    return 0;
}
