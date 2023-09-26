#include <bits/stdc++.h>

using namespace std;
const int MAXN=2e5+10;

int a[MAXN];
int n,x,i,j,result;
bool have_gondola_yet[MAXN];

int main() {
	cin >> n >> x;

	for (int i=0; i<n; i++) cin >> a[i];

	sort(a, a+n);
	i = 0; j = n - 1;
	while (i < j) {
		if (a[i] + a[j] > x) {
			--j;
		} else {
			++result;
			have_gondola_yet[i] = have_gondola_yet[j] = true;
			++i; --j;
		}
	}

	for (int i=0; i<n; i++) {
		result += have_gondola_yet[i] == false;
	}
	cout << result << "\n";
}
