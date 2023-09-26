#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

set<string> st_set;

void swap(char* a, int i, int j) {
	char c = a[i];
	a[i] = a[j];
	a[j] = c;
}

void permutation(char* a, int n) {
	if (n == 1) {
		st_set.insert(string(a));
		return;
	}
	for (int i=0; i<n; i++) {
		swap(a, i, n-1);
		permutation(a, n-1);
		swap(a, i, n-1);
	}
}

void permutation(string str) {
	int n = str.length();
	char* a = new char[n];
	for (int i=0; i<n; i++)
		a[i] = str[i];
	permutation(a, n);
}

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

	string str;
	cin>>str;
	permutation(str);
	cout << st_set.size();
	for (auto it=st_set.begin(); it!=st_set.end(); ++it) {
		cout << "\n" << *it;
	}
}