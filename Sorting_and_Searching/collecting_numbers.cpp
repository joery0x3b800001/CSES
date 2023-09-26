#include <bits/stdc++.h>

using ull = unsigned long long;
using namespace std;

int main() {
	ull n, val;
	cin >> n;

	ull collect[n];
	for (ull i=0; i<n; i++) {
		cin >> val;
		collect[val] = i;
	}

	ull total = 1;
	for (ull i=2; i<n+1; i++)
		total += (collect[i] < collect[i-1]);

	cout << total;
}