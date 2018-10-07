#include <stdio.h>
#include <memory.h>

class Bitmap{
private:
    int N;
    char* M;
public:
    Bitmap(int n = 8){
        M = new char[N = (n+7) / 8];
        memset(M, 0, N);
    }
    ~Bitmap(){
        delete [] M;
        M = NULL;
    }
    void set(int k){
        expand(k);
        M[ k >> 3 ] |= (0x80 >> (k & 0x07));
    }
    void reset( int k ){
        expand(k);
        M[ k >> 3 ] &= ~(0x80 >> (k & 0x07));
    }

    bool test(int k){
        expand(k);
        return M[ k >> 3 ] & (0x80 >> (k & 0x07));
    }
    void expand( int k ){
        if( k < 8*N ){
            return;
        }
        int oldN = N;
        char * oldM = M;
        M = new char[ N = (2*k + 7) / 8 ];
            memcpy( M,oldM, oldN );
        delete[] oldM;
    }
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

char readCapitalletter(){
    char ch = getchar();
    while ( !(ch >= 'A' && ch <= 'Z') )
        ch = getchar();
    return ch;
}

int main(){
    setvbuf(stdin, new char[1 << 17], _IOFBF, 1 << 17);
    setvbuf(stdout, new char[1 << 17], _IOFBF, 1 << 17);
	int n, m;
    n = readNumber();
    m = readNumber();

    Bitmap login(n+1);
    int *code = new int[n+1];

	char op;
	int op_id;
	int op_code;

	long int sum = 0;
	unsigned long int count = 0;
	int initializetime = 0;
	int * logintime = new int[n+1];
	memset(logintime, 0, n+1);

    for(int i = 0; i < m; i++){
		op = readCapitalletter();
		switch (op){
			case 'I':
				//scanf("%d %d", &op_id, &op_code);
				op_id = readNumber();
				op_code = readNumber();
				if (login.test(op_id) && (logintime[op_id]==initializetime+1) ) {
					code[op_id] = op_code;
				}
				else {
                    logintime[op_id] = initializetime + 1;
					login.set(op_id);
					code[op_id] = op_code;
					count += 1;
				}
				break;
			case 'O':
				//scanf("%d", &op_id);
				op_id = readNumber();
				if (login.test(op_id) && (logintime[op_id]==initializetime+1) ) {
					login.reset(op_id);
					count -= 1;
				}
				break;
			case 'C':
                initializetime += 1;
				count = 0;
				break;
			case 'N':
				sum += count;
				break;
			case 'Q':
				//scanf("%d", &op_id);
				op_id = readNumber();
				if( login.test(op_id) && (logintime[op_id]==initializetime+1)){
                    sum += code[op_id];
				} else {
                    sum -= 1;
				}
				break;
			default:
				break;
		}
	}
	printf("%ld", sum);
	return 0;
}



