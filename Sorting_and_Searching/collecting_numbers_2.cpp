#include <bits/stdc++.h>

using namespace std;

array<int, 200004> X;
int main() {
    int n, x, result = 1;
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> x;
        X[x] = i;
    }
    for (int i=1; i<=n; i++) {
        result += (X[i] < X[i-1]);
    }
    cout << result;
}