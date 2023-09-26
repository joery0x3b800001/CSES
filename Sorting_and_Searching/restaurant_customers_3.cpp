#include <bits/stdc++.h>

using namespace std;

int main() {
	int n,m;
	cin >> n >> m;
	vector<int> v(n);

	for (int i=0; i<n; i++) cin >> v[i];
	int cnt=n, sum=0, c=0;
	
	sort(v.begin(), v.end());
	int i = 0, j = n - 1;

	while (i < j) {
		if (v[i] + v[j] <= m) {cnt--; i++; j--;}
		else j--;
	}

	cout << cnt << '\n';
}