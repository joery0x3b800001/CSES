#include <bits/stdc++.h>

using namespace std;

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

	int N;
	cin>>N;
	if (N == 1) cout<<1; return 1;
    long long turns = 0;
    int lo = 0;
    for (int i = 0; i<N; i++) {
    	int x;
    	cin >> x;
        if (x<lo) {
            turns += lo - x;
        } else {
            lo = x;
        }
    }
    cout << turns;
}