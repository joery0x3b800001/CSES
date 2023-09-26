#include <iostream>
#include <vector>

using namespace std;

bool isConsistent(vector<int> q, int n) {
	for (int i = 0; i < n; i++) {
		if (q[i] == q[n]) return false;
		if ((q[i] - q[n]) == (n - i)) return false;
		if ((q[n] - q[i]) == (n - i)) return false;
	}
	return true;
}

void printQueen(vector<int> q) {
	int n = q.size();
	for (int i = 0; i < n; i++ ) {
		for (int j = 0; j < n; j++) {
			if (q[i] == j) cout << "Q ";
			else 		   cout << "* ";
		}
		cout << '\n';
	}
	cout << '\n';
}

void enumerate(vector<int> q, int k) {
	int n = q.size();
	if (k == n) printQueen(q);
	else {
		for (int i = 0; i < n; i++) {
			q[k] = i;
			if (isConsistent(q, k)) enumerate(q, k+1);
		}
	}
}

void enumerate(int n) {
	vector<int> a(n);
	enumerate(a, 0);
}

int main() {
	int n; cin >> n;
	enumerate(n);
	return 0;
}