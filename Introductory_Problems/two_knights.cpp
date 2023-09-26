#include <bits/stdc++.h>

using namespace std;

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	long long k;

	cin>>k;
	for (long n=1; n<=k; ++n) {
		cout<<(n*n)*(n*n-1)/2 - 4*(n-1)*(n-2)<<"\n";
	}
}