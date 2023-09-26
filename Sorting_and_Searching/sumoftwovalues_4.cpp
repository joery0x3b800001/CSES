#include <bits/stdc++.h>

using namespace std;

int main() {
	int n,target;
	cin >> n >> target;

	array<pair<int,int>, 200004> values;

	for (int i=0; i<n; i++) {
		int x;
		cin >> x;
		values[i] = {x, i+1};
	}

	sort(values.begin(), values.begin()+n);
	int left = 0;
	int right = n-1;

	while (left < right) {
		if (values[left].first + values[right].first > target) {
			right--;
		} else if (values[left].first + values[right].first < target) {
			left++;
		} else if (values[left].first + values[right].first == target) {
			cout << values[left].second << " " << values[right].second;
			return 0;
		}
	}
	cout << "IMPOSSIBLE\n";
}