#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	long n,sum=0;
	cin>>n;
	while (n) {
		n /= 5;
		sum+=n;
	}
	cout << sum;
}