#include <bits/stdc++.h>

using namespace std;

array<int, 200004> X, P;
int check(int a, int b) {
	int sum = 0;
	if (X[a-1] > X[a]) sum++;
	if (X[a+1] < X[a]) sum++;
	if (X[b-1] > X[b]) sum++;
	if (X[b+1] < X[b]) sum++;
	if (a - b == 1 && X[a] < X[b]) sum--;
	if (b - a == 1 && X[b] < X[a]) sum--;
	return sum;
}

int main() {
	int n,m,a,b,x,result = 1;
	cin>>n>>m;
	X[n+1] = n+1;
	for (int i=1; i<=n; i++) {
		cin >> x;
		P[i] = x;
		X[x] = i;
	}

	for (int i=1; i<=n; i++) {
		result += X[i] < X[i-1];
	}

	while (m--) {
		cin>>a>>b;
		swap(P[a], P[b]);
		a = P[a], b = P[b];
		result -= check(a, b);
		swap(X[a], X[b]);
		result += check(a, b);
		cout << result << '\n';
	}
}