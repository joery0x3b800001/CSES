#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n,m;
	cin >> n >> m;
	vector<ll> v(n);

	ll p;
	for (int i=0; i<n; i++)
	{
		cin >> v[i];
	}

	sort(v.begin(), v.end());

	for (int i=0; i<m; i++)
	{
		cin >> p;
		if (p < v.front()) {
			cout << -1 << '\n';
		} else {
			if (p >= v.back()) {
				cout << v.back() << '\n';
				v.pop_back();
			} 
			else {
				auto it = lower_bound(v.begin(), v.end(), p);
				--it;
				cout << (*it) << '\n';
				v.erase(it);
			}
		}
	}
}