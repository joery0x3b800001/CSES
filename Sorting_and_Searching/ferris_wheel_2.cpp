#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;
const int MAXN=2e5+10;

int a[MAXN];
int n,x,i,j,result;

inline int readInt() {
    int result = 0;
    int c;
    for (; (c = ::getchar()) < '0';);
    for (result = c - '0'; (c = ::getchar()) >= '0';) {
        result *= 10;
        result += c - '0';
    }
    return result;
}

int main() {
	n = readInt(); x = readInt();
	for (int i=0; i<n; i++) a[i] = readInt();
	sort(a, a+n);
	i = 0; j = n-1;
	while (i <= j) {
		if (a[i] + a[j] <= x) {
			++result;
			++i; --j;
		} else {
			++result;
			--j;
		}
	}
	cout << result << '\n';
}
