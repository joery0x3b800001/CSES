#include <bits/stdc++.h>

using namespace std;

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	long n;
	cin>>n;

	if (n==1) cout << 1;
	if (n==2 || n==3) cout << "NO SOLUTION";
	if (n>=4) {
		for (long i=2; i<=n; i+=2) printf("%ld ", i);
		for (long i=1; i<=n; i+=2) printf("%ld ", i);
	}
}