#include <stdio.h>
#include <string.h>

int readNumber(){
	int number = 0;
	char ch = getchar();
	while( ch < '0' || ch > '9' )
		ch = getchar();
	while( ch >= '0' && ch <= '9' ){
		number = number * 10 + ch - '0';
		ch = getchar();
	}
	return number;
}

int main() {
	setvbuf(stdin, new char[1 << 17], _IOFBF, 1 << 17);
	int n, k;
	int** array;
	array = new int*[3];
	bool* arranged;
	//scanf("%d", &n);
	n = readNumber();
	for (int i = 0; i < 3; i++) {
		array[i] = new int[n];
		for (int j = 0; j < n; j++) {
			//scanf("%d", &array[i][j]);
			array[i][j] = readNumber();
		}
	}
	//scanf("%d", &k);
	k = readNumber();
	arranged = new bool[n];
	memset(arranged, false, n);
	int num;
	while (true) {
		static int countA = 0;
		num = array[0][countA];
		while (arranged[num - 1]) {
			countA++;
			num = array[0][countA];
		}
		if (num == k) {
			printf("A");
			return 0;
		}
		arranged[num - 1] = true;
		++countA;
		static int countB = 0;
		num = array[1][countB];
		while (arranged[num - 1]) {
			countB++;
			num = array[1][countB];
		}
		if (num == k) {
			printf("B");
			return 0;
		}
		arranged[num - 1] = true;
		++countB;

		static int countC = 0;
		num = array[2][countC];
		while (arranged[num - 1]) {
			countC++;
			num = array[2][countC];
		}
		if (num == k) {
			printf("C");
			return 0;
		}
		arranged[num - 1] = true;
		++countC;
	}
	return 1;
}
