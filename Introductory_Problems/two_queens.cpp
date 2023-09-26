#include <bits/stdc++.h>
#define MAX 10001

using namespace std;

// inline char* read() {
// 	char buffer[MAX];
// 	int i, ch;

// 	for (i=0; (i < MAX) && ((ch = getchar()) != EOF); ++i)
// 		buffer[i] = ch;

// 	return (char*)buffer;
// }

int main() {
	bool ok[8][8];
	int result = 0;

	for (int i=0; i<8; i++) {
		string s;
		cin >> s;
		for (int j=0; j<8; j++) {
			ok[i][j] = (s[j] == '.');
		}
	}
	vector<int> vals(8);

	iota(vals.begin(), vals.end(), 0);

	do {
		bool works = true;
		bool blocked[16];
		for (int i=0; i<8; i++) {
			if (!ok[i][vals[i]]) {
				works = false;
			}
		}

		memset(blocked, false, sizeof blocked);
		for (int i=0; i<8; i++) {
			if (blocked[i+vals[i]]) {
				works = false;
			}
			blocked[i+vals[i]] = true;
		}

		memset(blocked, false, sizeof blocked);
		for (int i=0; i<8; i++) {
			if (blocked[i + 7 - vals[i]]) {
				works = false;
			}
			blocked[i + 7 - vals[i]] = true;
		}
		if (works) result++;
	} while(next_permutation(vals.begin(), vals.end()));

	cout << result << '\n';
}