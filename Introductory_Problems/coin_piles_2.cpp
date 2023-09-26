#include <bits/stdc++.h>
#pragma GCC optimize("Oz")

using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0)->sync_with_stdio(0);
	long t,a,b,x,y;
	cin>>t;
	while (t--) {
		cin>>a>>b;
		y = (2 * b - a) / 3;
		x = b - 2 * y;
		if (x >= 0 && y >= 0 && a == 2 * x + y && b == 2 * y + x) cout << "YES\n";
		else cout << "NO\n";
	}
}