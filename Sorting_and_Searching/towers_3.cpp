#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;

	vector<int> v;
	for (int i=0; i<n; i++) {
		int curr;
		cin >> curr;

		auto it = upper_bound(v.begin(), v.end(), curr);

		if (it == v.end()) {
			v.push_back(curr);
		} else {
			(*it) = curr;
		}
	}
	cout << v.size() << '\n';
}