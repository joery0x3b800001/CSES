#include <bits/stdc++.h>

using namespace std;

bool maze[10][10], vis[10][10];
int result = 0;


bool check(int x, int y) {
	for (int i=1; i<=8; i++) {
		for (int j=1; j<=8; j++) {
			if (vis[i][j]) {
				if (abs(i - x) == abs(j - y)) return false;
				if (i == x || j == y) return false;
			}
		}
	}
	return true;
}


void dfs(int cur) {
	if (cur > 8) {
		result++;
		return;
	}

	for (int i=1; i<=8; i++) {
		if (check(cur, i) && maze[cur][i]) {
			vis[cur][i] = 1;
			dfs(cur + 1);
			vis[cur][i] = 0;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	memset(maze, 0, sizeof maze);
	memset(vis, 0, sizeof vis);

	for (int i=1; i<=8; i++) {
		string s; getline(cin, s);
		for (int j=1; j<=8; j++) {
			if (s[j-1] == '.') maze[i][j] = 1;
		}
	}
	dfs(1);
	cout << result << '\n';
}