#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> playlist(n);

	for (int i=0; i<n; i++) {
		cin >> playlist[i];
	}

	size_t left = 0, right = 0, maxLength = 0;
	unordered_set<int> seen;

	while (right < n) {
		int song = playlist[right];
		if (seen.count(song) == 0) {
			seen.insert(song);
			maxLength = max(maxLength, right - left + 1);
			right++;
		} else {
			seen.erase(playlist[left]);
			left++;
		}
	}
	cout << maxLength << '\n';
}