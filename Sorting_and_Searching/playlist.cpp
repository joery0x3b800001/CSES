#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;

	int a[n];
	for (int i=0; i<n; i++) {
		cin >> a[i];
	}

	map<int,int> mp;
	int result = 0;

	for (int i=0, j=0; i<n; i++) {
		j = max(mp[a[i]], j);
		result = max(result, i-j+1);
		mp[a[i]] = i+1;
	}
	cout << result << '\n';
}