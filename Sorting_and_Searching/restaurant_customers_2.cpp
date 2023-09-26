#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<pair<int,int>> times;
	for (int i=0; i<n; i++) {
		int start, end;
		cin >> start >> end;
		times.push_back({start, 1});
		times.push_back({end, -1});
	}

	sort(times.begin(), times.end());

	int curr = 0;
	int at = 0;

	vector<int> ppl_change(2 * n);

	for (int i=0; i<2*n; i++) {
		if (i == 0) {
			times[i].first = 0;
		} else if (times[i].first > curr) {
			at++;
			curr = times[i].first;
		}
		ppl_change[at + 1] += times[i].second;
	}

	vector<int> ppl_amt(2 * n + 1);
	for (int i=1; i < 2 * n; i++) {
		ppl_amt[i] = ppl_change[i] + ppl_amt[i - 1];
	}

	int max_ppl = 0;
	for (int i=0; i < 2 * n; i++) {
		max_ppl = max(max_ppl, ppl_amt[i]);
	}

	cout << max_ppl << '\n';
}