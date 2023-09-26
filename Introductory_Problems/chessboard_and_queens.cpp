#include <stdio.h>

char DESK[8][8]; int P = 0; int TMP[8];

bool check(int i, int ins) {
	int count = 0;
	for (int j=0; j<ins; j++) {
		if (TMP[j] != i && ((ins - j)*(ins - j) != (TMP[j] - i)*(TMP[j] - i))) count++;
	}
	if (count == ins) return true;
	else return false;
}

void COUNT(int ins) {
	if (ins == 7) {
		for (int i=0; i<8; i++) {
			if (DESK[i][ins] == '.' && check(i, ins)) P++;
		}
	} else {
		for (int i=0; i<8; i++) {
			if (DESK[i][ins] == '.' && check(i, ins)) {TMP[ins] = i; COUNT(ins + 1);}
		}
	}
}

int main() {
	for (int i=0; i<8; i++) {
		for (int j=0; j<9; j++) {
			if (j == 8) getchar();
			else DESK[i][j] = getchar();
		}
	}

	COUNT(0);
	printf("%d", P);
}