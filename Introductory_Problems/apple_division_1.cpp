#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;
#define ln '\n'

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	vector<long long> p(n);
	for (auto &i : p) cin >> i;
	int hn = n/2;
	vector<long long> sl(1<<hn), sr(1<<(n-hn));
	for (int i=0; i<1<<hn; i++) {
		for (int j=0; j<hn; j++) {
			if (i>>j&1) sl[i]+=p[j];
		}
	}

	for (int i=0; i<1<<(n-hn); i++) {
		for (int j=0; j<n-hn; j++) {
			if (i>>j&1) sr[i]+=p[hn+j];
		}
	}

	sort(sr.begin(), sr.end(), greater<>());
	long long su = accumulate(p.begin(), p.end(), 0LL), re=su;
	for (auto i : sl) {
		auto ptr = lower_bound(sr.begin(), sr.end(), su/2-i, greater<>());
		if (ptr!=sr.end()) re=min(re,su-2*(i+*ptr));
	}
	cout << re << '\n';
}
