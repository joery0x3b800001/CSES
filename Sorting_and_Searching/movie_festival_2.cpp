#include <bits/stdc++.h>

#define pii pair<int,int>
using namespace std;

bool cmp(pii a, pii b) {
	if (a.second != b.second) return a.second < b.second;
	return a.first < b.first;
}

array<pii, 200004> P;

int main() {
	int n, l, r, result = 0;
	cin >> n;

	for (int i=0; i<n; i++) {
		cin >> l >> r;
		P[i] = {l, r};
	}

	sort(P.begin(), P.begin()+n, cmp);

	l = 0;
	for (pii p : P) {
		if (p.first >= l) {
			result++;
			l = p.second;
		}
	}

	cout << result;
}