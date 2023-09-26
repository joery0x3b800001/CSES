#include <bits/stdc++.h>
using st = size_t;

using namespace std;

int main() {
	st n,i,j,value,s;
	cin>>n>>s;

	array<pair<st,st>, 200004> vp;
	for (st i=0; i<n; i++) {
		cin >> value;
		vp[i] = {value, i+1};
	}
	sort(vp.begin(), vp.begin()+n);

	i = 0; j = n-1;
	while (i < j) {
		if (vp[i].first + vp[j].first == s && i != j) {
			cout << vp[j].second << " " << vp[i].second << '\n';
			++i; --j;
			return 0;
		} else {
			--j;
		}
	}
	cout << "IMPOSSIBLE";
}