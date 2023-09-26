#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using ll = long;

using namespace std;

ll readInt() {
	bool minus = false;
	ll result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	return (minus) ? -result : result;
}

int main() {
	ios_base::sync_with_stdio(0);
	unordered_set<ll> st;
	
	int n; n = readInt();

	while (n--) {
		st.insert(readInt());
	}

	cout << st.size() << '\n';
}