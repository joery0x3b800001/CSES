#include <bits/stdc++.h>

using ll = long long;
using namespace std;


int main() {
	int n;
	cin >> n;

	ll coins[n];
	for (int i=0; i<n; i++) cin >> coins[i];

	sort(coins, coins+n);

	ll smallestSum = 1;
	for (int i=0; i<n && smallestSum >= coins[i]; i++) 
		smallestSum += coins[i];
	cout << smallestSum << '\n';
}


//for a[i] > k+1,the largest sum we can create is k, and not k+1