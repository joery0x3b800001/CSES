#include <bits/stdc++.h>

using namespace std;

void rec(int n, int from, int with, int to) {
    if(n == 0) return;
    rec(n - 1, from, to, with);
    cout << from << ' ' << to << endl;
    rec(n - 1, with, from, to);
}
 
void solve() {
    int n; cin >> n;
    cout << (1 << n) - 1 << endl;
    rec(n, 1, 2, 3);
}

int main() {
    solve();
}