#include <bits/stdc++.h>

using namespace std;

int n;
set<int> s;
int a[200000], result;

int main() {
	int r = -1;
	cin >> n;
	for (int i=0; i<n; i++) cin >> a[i];
	for (int i=0; i<n; i++) {
		while (r < n - 1 && !s.count(a[r + 1])) s.insert(a[++r]);
		result = max(result, r - i + 1);
		s.erase(a[i]);
	}

	cout << result << '\n';
}