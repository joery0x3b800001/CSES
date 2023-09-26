#include <iostream>
#include <vector>
#include <algorithm>
#pragma GCC optimize("O3")

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	int arrival[n];
	int departure[n];

	for (int i=0; i<n; i++) {
		cin >> arrival[i] >> departure[i];
	}

	sort(arrival, arrival+n);
	sort(departure, departure+n);

	int i = 0;
	int j = 0;
	int customers = 0;
	int max_customers = 0;

	while (i < n && j < n) {
		if (arrival[i] < departure[j]) {
			customers++;
			i++;
		} else {
			customers--;
			j++;
		}
		max_customers = max(max_customers, customers);
	}

	cout << max_customers << '\n';
}