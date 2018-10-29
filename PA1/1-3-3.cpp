#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

struct CharNode {
	char ch;
	CharNode * last;
	CharNode * next;
}head, tile;

struct CharNode *Lcursor, *Rcursor;

int relativePos = 1;     // -1: Rcursor --- Lcursor  0: Rcursor     1: Lcursor -- Rcursor
													//  Lcursor
int readNumber() {
	int number = 0;
	char ch = getchar();
	while (ch < '0' || '9' < ch)
		ch = getchar();
	while ('0' <= ch && ch <= '9') {
		number = number * 10 + ch - '0';
		ch = getchar();
	}
	return number;
}

char readCharacter() {
	char ch = getchar();
	while (ch < 33 || 126 < ch)
		ch = getchar();
	return ch;
}

int readCMD() {
	char ch;
rp:
	ch = getchar();
	switch (ch) {
	case '<':
		ch = readCharacter();
		return ch == 'L' ? -1 : 1;
	case '>':
		ch = readCharacter();
		return ch == 'L' ? -2 : 2;
	case 'I':
		ch = readCharacter();
		return ch == 'L' ? -3 : 3;
	case 'D':
		ch = readCharacter();
		return ch == 'L' ? -4 : 4;
	case 'R':
		return 5;
	case 'S':
		return 6;
	default:
		goto rp;
	}
}

void readLine(string & text) {
	char ch = getchar();
	while (ch != '\n') {
		text.append(&ch);
		ch = getchar();
	}
}

void reversePtr(struct CharNode* target) {
	struct CharNode* mid = target->last;
	target->last = target->next;
	target->next = mid;
}

void correctDirection(struct CharNode* ptr, int direction) {    //-1----last 1----next
	if (direction == -1) {
		if (ptr->last->next != ptr) {
			reversePtr(ptr->last);
//			assert(ptr->last->next == ptr);
		}
	}
	else {
		if (ptr->next->last != ptr) {
			reversePtr(ptr->next);
//			assert(ptr->next->last == ptr);
		}
	}
}

void printText() {
	struct CharNode* ptr = &head;
	while (ptr != &tile) {
		correctDirection(ptr, 1);
		ptr = ptr->next;
		printf("%c", ptr->ch);
	}
}

void Initialize(string text) {
	struct CharNode* last = &head;
	for (int i = 0, len = text.length(); i < len; i++) {
		struct CharNode* letter = new struct CharNode;
		letter->ch = text[i];
		letter->last = last;
		last->next = letter;
		last = letter;
	}
	last->next = &tile;
	tile.last = last;
	tile.ch = '\n';
	Lcursor = &head;
	Rcursor = tile.last;
}

void MoveToLeft(int cmd) {
	if (cmd == -1) {
		if (Lcursor == &head) {
			printf("F\n");
			return;
		}
		correctDirection(Lcursor, -1);
		Lcursor = Lcursor->last;
		if (Lcursor == Rcursor) {
			relativePos = 0;
		}
		else if (relativePos == 0) {
			relativePos = 1;
		}
		printf("T\n");
	}
	else {
		if (Rcursor == &head) {
			printf("F\n");
			return;
		}
		correctDirection(Rcursor, -1);
		Rcursor = Rcursor->last;
		if (Lcursor == Rcursor) {
			relativePos = 0;
		}
		else if (relativePos == 0) {
			relativePos = -1;
		}
		printf("T\n");
	}
}

void MoveToRight(int cmd) {
	if (cmd == -2) {
		if (Lcursor->next == &tile) {
			printf("F\n");
			return;
		}
		correctDirection(Lcursor, 1);
		Lcursor = Lcursor->next;
		if (Lcursor == Rcursor) {
			relativePos = 0;
		}
		else if (relativePos == 0) {
			relativePos = -1;
		}
		printf("T\n");
	}
	else {
		if (Rcursor->next == &tile) {
			printf("F\n");
			return;
		}
		correctDirection(Rcursor, 1);
		Rcursor = Rcursor->next;
		if (Lcursor == Rcursor) {
			relativePos = 0;
		}
		else if (relativePos == 0) {
			relativePos = 1;
		}
		printf("T\n");
	}
}

void Insert(int cmd, char ch) {
	if (cmd == -3) {
		correctDirection(Lcursor, 1);
		struct CharNode* letter = new struct CharNode;
		letter->ch = ch;  letter->last = Lcursor;  letter->next = Lcursor->next;
		Lcursor->next->last = letter;  Lcursor->next = letter;
		Lcursor = Lcursor->next;
		if (relativePos == 0) {
			Rcursor = Lcursor;
		}
	}
	else {
		correctDirection(Rcursor, 1);
		struct CharNode* letter = new struct CharNode;
		letter->ch = ch;  letter->last = Rcursor;  letter->next = Rcursor->next;
		Rcursor->next->last = letter;  Rcursor->next = letter;
		Rcursor = Rcursor->next;
		if (relativePos == 0) {
			Lcursor = Rcursor;
		}
	}
	printf("T\n");
}

void Myerase(int cmd) {
	if (cmd == -4) {
		if (Lcursor->next == &tile) {
			printf("F\n");
			return;
		}
		correctDirection(Lcursor, 1);
		correctDirection(Lcursor->next, 1);
		if (Lcursor->next == Rcursor) {
			Rcursor = Lcursor;
			relativePos = 0;
		}
		Lcursor->next->next->last = Lcursor;
		struct CharNode* temp = Lcursor->next;
		Lcursor->next = Lcursor->next->next;
		delete temp;
	}
	else {
		if (Rcursor->next == &tile) {
			printf("F\n");
			return;
		}
		correctDirection(Rcursor, 1);
		correctDirection(Rcursor->next, 1);
		if (Rcursor->next == Lcursor) {
			Lcursor = Rcursor;
			relativePos = 0;
		}
		Rcursor->next->next->last = Rcursor;
		struct CharNode* temp = Rcursor->next;
		Rcursor->next = Rcursor->next->next;
		delete temp;
	}
	printf("T\n");
}

void reverse() {
	if (relativePos == 1) {
		if (Lcursor->next == Rcursor) {
			printf("T\n");
			return;
		}
		correctDirection(Lcursor, 1);
		correctDirection(Rcursor, 1);
		struct CharNode *LO, *LI, *RO, *RI;
		LO = Lcursor;
		LI = Lcursor->next;
		RI = Rcursor;
		RO = Rcursor->next;
//		assert(LI->last == LO);
//		assert(RI->next == RO);
		reversePtr(LI);  reversePtr(RI);
//		assert(LI->next == LO);
//		assert(RI->last == RO);
		LO->next = RI;  RI->last = LO;
		LI->next = RO;  RO->last = LI;
		Rcursor = LI;
		printf("T\n");
	}
	else {
		printf("F\n");
	}
}

int main() {
	setvbuf(stdin, new char[1 << 18], _IOFBF, 1 << 18);
	setvbuf(stdout, new char[1 << 18], _IOFBF, 1 << 18);
	string text;
	readLine(text);

	Initialize(text);

	const int N = readNumber();
	int cmd;
	char character;
	for (int count = 0; count < N; ++count) {
		cmd = readCMD();
		switch (cmd) {
		case -1:
		case 1:
			MoveToLeft(cmd);
			break;
		case -2:
		case 2:
			MoveToRight(cmd);
			break;
		case -3:
		case 3:
			character = readCharacter();
			Insert(cmd, character);
			break;
		case -4:
		case 4:
			Myerase(cmd);
			break;
		case 5:
			reverse();
			break;
		case 6:
			printText();
			break;
		default:
			return -1;
		}
	}

	return 0;
}
