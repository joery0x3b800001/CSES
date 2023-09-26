#include <bits/stdc++.h>

using namespace std;

int a[200005];
int n,m,k,result,aa;

int main() {
	cin >> n >> m >> k;
	for (int i=0; i<n; i++) {
		cin >> a[i];
	}

	sort(a,a+n);

	multiset<int> s;
	for (int i=0; i<m; i++) {
		cin >> aa;
		s.insert(aa);
	}

	for (int i=0; i<n; i++) {
		int val = a[i]-k;
		auto it = s.lower_bound(val);
		if (it != s.end() && *it <= a[i]+k) {
			s.erase(it);
			result++;
		}
	}
	cout << result;
	return 0;
}