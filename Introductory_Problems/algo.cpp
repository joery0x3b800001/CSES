#include <bits/stdc++.h>

// https://cses.fi/
using namespace std;

int main() {
	long n;
	cin>>n;

	cout<<n;
	while (n!=1) {
		if (!(n%2)) n/=2;
		else if ((n%2)) n=n*3+1;
		cout<<" "<<n;
	}
}