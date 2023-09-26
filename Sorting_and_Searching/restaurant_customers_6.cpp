#include <bits/stdc++.h>
using namespace std;
using ll = size_t;

int main() {
    int n;
    cin >> n;

    vector<ll> arrivals(2*n, 0);

    for (int i = 0; i < n; i++) {
        ll  a, b;
        cin >> a >> b;
        arrivals[a]++;
        arrivals[b]--;
    }

    ll ans = 0, curr = 0;

    for (auto & x : arrivals) {
        curr += x;
        ans = max(ans, curr);
    }

    cout << ans << endl;

    return 0;
}
