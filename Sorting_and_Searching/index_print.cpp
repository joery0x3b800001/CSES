#include <bits/stdc++.h>

using namespace std;

int main() {
	int n,s,value;
	cin >> n >> s;

	vector<pair<int,int>> values(n);

	for (int i=0; i<n; i++) {
		int value; cin >> value;
		values[i] = make_pair(value, i+1);
	}

	cout << values[6607].first << " " << values[6607].second << '\n';

	cout << values[91822].first << " " << values[91822].second << '\n';
}