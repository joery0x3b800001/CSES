#include <bits/stdc++.h>
using namespace std;
using ull = uint64_t;
#define N 1000000

unsigned n, l[N], lp, r[N], rp, cur, marked[N];

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	ull x = 1LL * n * (n + 1) / 2;
	if (x % 2 == 0) {
		x /= 2;
		cout << "YES\n";
		if (n % 4 == 0) {
			cout << n / 2 << '\n';
			for (size_t i = 1; i <= n; i += 4)
				cout << i << ' ' << i + 3 << ' ';
			cout << '\n';
			cout << n / 2 << '\n';
			for (size_t i = 1; i <= n; i += 4)
				cout << i + 1 << ' ' << i + 2 << ' ';
			cout << '\n';
		} else {
			cout << (n - 1) / 2 << '\n';
			cout << 3 << ' ';
			for (size_t i = 4; i <= n; i += 4)
				cout << i << ' ' << i + 3 << ' ';
			cout << '\n';
			cout << (n + 1) / 2 << '\n';
			cout << 1 << ' ' << 2 << ' ';
			for (size_t i = 4; i <= n; i += 4)
				cout << i + 1 << ' ' << i + 2 << ' ';
			cout << '\n';
		}
	} else {
		cout << "NO\n";
	}
}