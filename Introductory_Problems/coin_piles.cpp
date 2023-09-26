#include <bits/stdc++.h>
using ull = uint64_t;
using namespace std;

void solve() {
	ull a, b;
	cin>>a>>b;

	while (1) {
		if (a > b) swap(a,b);

		ull A = min(a / 1, b - a);
		ull B = min(b / 2, b - a);
		ull t = max(A,B);
		if (t == 0) break;
		a -= t;
		b -= t * 2;
	}

	ull t = min(a,b) / 3;
	a -= t * 3;
	b -= t * 3;

	cout << (a == 0 && b == 0 ? "YES\n" : "NO\n");
}

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	ull tt;
	cin >> tt;
	while(tt--) {
		solve();
	}
	return 0;
}