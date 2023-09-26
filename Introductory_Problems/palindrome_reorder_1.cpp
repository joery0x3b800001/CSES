#include <bits/stdc++.h>
#include <unistd.h>
#define ull unsigned long long
using namespace std;

char ibuf[1000001];
char obuf[1000001];
ull cnt[256];

int main() {
	ull n = read(0, ibuf, 1000001);
	n--;
	for (ull i=0; i<n; i++)
		cnt[ibuf[i]]++;
	bool mid = false;
	ull off = 1;
	for (char c='A'; c<='Z'; c++) {
		ull a = cnt[c];
		if (!a)
			continue;
		if (a & 1) {
			if (!(n & 1) || mid) {
				cout << "NO SOLUTION\n";
				return 0;
			}
			obuf[n >> 1] = c;
			mid = true;
			a--;
		}
		ull h = a >> 1;
		memset(obuf + off - 1, c, h);
		memset(obuf + n + 1 - off - h, c, h);
		off += h;
	}
	write(1, obuf, n);
}
