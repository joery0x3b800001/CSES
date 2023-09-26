#include <stdio.h>

#define PU putchar_unlocked
#pragma GCC optimize("O3")

inline int getNum() {
	char c;
	int x = 0;

	while ((c = getchar_unlocked()) && c != '\n' && c != ' ')
		x = x * 10 + c - '0';
	return x;	
}

inline void putNum(int x) {
	char num[10];
	short i = 0;
	while (x > 0) {
		num[i++] = (x % 10) + '0';
		x /= 10;
	}

	while (i-- > 0)
		PU(num[i]);
}

int main() {
	int t,a,b,x,y;

	t = getNum();

	while (t--) {
		a = getNum();
		b = getNum();
		y = (2 * b - a) / 3;
		x = b - 2 * y;
		if (x >= 0 && y >= 0 && a == 2 * x + y && b == 2 * y + x) {
			PU('Y');
			PU('E');
			PU('S');
			PU('\n');
		} else {
			PU('N');
			PU('O');
			PU('\n');
		}
	}
}