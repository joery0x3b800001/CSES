#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i=0; i<n; i++) cin >> nums[i];

	set<int> window;
	int back = 0;
	int result = 0;
	for (int i=0; i<n; i++) {
		if (nums.count(nums[i])) {
			window.insert(nums[i]);
		}
		else {
			while(nums[back] != nums[i]) {
				window.erase(window.find(nums[back++]));
			}
			back++;
		}
		result = max(result, i - back + 1);
	}

	cout << result << '\n';
}