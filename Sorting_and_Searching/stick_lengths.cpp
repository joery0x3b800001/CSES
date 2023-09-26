#include <bits/stdc++.h>
using ll = long long;

using namespace std;

int main() {
	int n;
	cin >> n;

	ll values[n];
	for (int i=0; i<n; i++) cin >> values[i];

	sort(values, values+n);

	ll mid = values[n/2], sum = 0;
	for (int i=0; i<n; i++) {
		sum += abs(values[i] - mid);
	}

	cout << sum << '\n';
}