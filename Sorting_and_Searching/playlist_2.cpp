#include <bits/stdc++.h>

using namespace std;

map<int,int> M;
set<int> S;
int main() {
	int n;
	cin >> n;
	size_t result = 0;
	queue<int> Q;

	while (n--)
	{
		int x; cin >> x;
		Q.push(x), M[x]++;
		if (M[x] == 2)
		{
			while (Q.front() != x) M[Q.front()]--, Q.pop();
			M[Q.front()]--, Q.pop();
			S.insert(Q.front());
		}
		result = std::max(result, Q.size());
	}
	cout << result;
}