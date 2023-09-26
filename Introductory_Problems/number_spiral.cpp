#include <bits/stdc++.h>
// #pragma GCC optimize("O3")

using namespace std;

inline long solve(long x, long y) {
	long z = x > y ? x : y;
	return z*z-~(z%2?y-x:x-y)-z;
}

int main() {
	// cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
	long t;
	cin>>t;

	while (t--) {
		long x, y;
		cin>>x>>y;
		cout << solve(x,y) << " ";
	}
}