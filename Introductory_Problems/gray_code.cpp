#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

long gray_encode(long n) {
	return n ^ (n >> 1);
}

long gray_decode(long n) {
	int p = n;
	while (n >>= 1) p ^= n;
	return p;
}

void fmtbool(long off,long n,char *buf) {
	char *b = buf + off;
	*b=0;
	do {
		*--b = '0' + (n & 1);
		n >>= 1;
	} while (b != buf);
}

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

	long n,g;
	cin >> n;
	char *bi = new char[n];

	for (int i=0; i<pow(2,n); i++) {
		g = gray_encode(i);
		fmtbool(n, g, bi);
		printf("%s\n", bi);
	}
}