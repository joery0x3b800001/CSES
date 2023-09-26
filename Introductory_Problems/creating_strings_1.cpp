#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define IOS ios_base::sync_with_stdio(0), cin.tie(0);

using namespace std;

int main() {
	IOS;
	int n;
	string s; cin >> s;
	int len = s.size(), num[30];
	memset(num, 0, sizeof num);
	for (int i=0; i<len; i++)
		num[s[i] - 'a'] += 1;

	string str;
	for (int i=0; i<26; i++)
		while(num[i])
			str += (char)(i + 'a'), num[i]--;
	vector<string> result;
	do {
		result.push_back(str);
	} while(next_permutation(str.begin(), str.end()));
	cout<<result.size();
	for (auto i : result) cout<<"\n"<<i;
	return 0;
}