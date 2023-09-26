#include <bits/stdc++.h>
using ll = long long;

using namespace std;

int main() {
	int n;
	cin >> n;

	ll values[n];
	for (int i=0; i<n; i++) cin >> values[i];

	ll max_now, global_max;
	max_now = global_max = values[0];

	for (int i=1; i<n; i++) {
		max_now = std::max(values[i], values[i] + max_now);
		if (max_now > global_max)
		{
			global_max = max_now;
		}
	}
	cout << global_max << '\n';
}