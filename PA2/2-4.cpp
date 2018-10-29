#include <stdio.h>

int n, m, pS = 0, pA = 1, currentID = 1;
int *A, *stack;

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
	setvbuf(stdin, new char[1 << 18], _IOFBF, 1 << 18);
    setvbuf(stdout, new char[1 << 18], _IOFBF, 1 << 18);

	n = readNumber();
	m = readNumber();
	A = new int[n+1];
	for(int i = 1; i <= n; i++){
		A[i] = readNumber();
	}
	stack = new int[m+1];
	stack[0] = -1;

    char **operation = new char*[2*n];
    int op = 0;
	while(pA <= n){
		if(A[pA] == currentID){
            operation[++op] = new char[4];
            sprintf(operation[op], "%d P\n", currentID);
            pA += 1;
            currentID += 1;
		}
		else if(stack[pS] == currentID){
			//OutS();
			operation[++op] = new char[4];
            sprintf(operation[op], "%d O\n", stack[pS]);
			pS -= 1;
			currentID += 1;
		}
		else{
			if(pS < m){
				//InS();
				operation[++op] = new char[4];
                sprintf(operation[op], "%d I\n", A[pA]);
				stack[++pS] = A[pA++];
			} else {
				printf("No");
				return 0;
			}
		}
	}
	while(0 < pS){
		if(stack[pS] == currentID){
            operation[++op] = new char[4];
            sprintf(operation[op], "%d O\n", stack[pS]);
            pS -= 1;
            currentID += 1;
		} else {
			printf("No");
			return 0;
		}
	}
	for(int i = 1; i <= op; i++){
        printf("%s", operation[i]);
	}
	return 0;
}
