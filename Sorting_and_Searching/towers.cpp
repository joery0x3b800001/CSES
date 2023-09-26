#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;
#define pb push_back
#define sz(x) (int)(x).size()

int n;
vi x;
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i=0; i<n; i++) {
		int z;
		cin >> z;
		int lo = 0, hi = sz(x);
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (x[mid] > z) hi = mid;
			else lo = mid + 1;
		}
		if (lo == sz(x)) x.pb(z);
		else x[lo] = z;
	}
	cout << sz(x);
}

