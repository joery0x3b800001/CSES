#include <bits/stdc++.h>

#define MOD 1e9+7
using namespace std;

template < typename T >
T modpow(T base, T exp, const T& modulus) {
	base %= modulus;
	T result = 1;
	while (exp > 0) {
		if (exp & 1) result = (result * base) % modulus;
		base = (base * base) % modulus;
		exp >>= 1;
	}
	return result;
}

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	long n;
	cin>>n;
	cout << modpow<long>(2, n, MOD);
}