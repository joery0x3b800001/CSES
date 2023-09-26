#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast")

#define N 200000

static inline int getint() {
    int x, y;
    while((x = getchar_unlocked()) < '0') {}
    x -= '0';
    while((y = getchar_unlocked()) >= '0') { x = x * 10 + y - '0'; }
    return x;
}

int main() {
    int p[N+2];
    int x[N+2];

    int n, m;
    n = getint(); m = getint();

    for (int i=1; i<=n; i++) {
        p[x[i] = getint()] = i;
    }

    x[N+1] = N+1;
    p[N+1] = N+1;

    int v = 1;
    for (int i=1; i<n; i++) {
        v += (p[i+1] < p[i]);
    }

    while (m--) {
        int a = getint(), b = getint();

        if (a != b) {
            int xa = x[a], xb = x[b];

            if (xb - xa == 1) {
                v += b > a ? 1 : -1;
                v += (b < p[xa-1]) - (a < p[xa-1]);
                v += (p[xb+1] < a) - (p[xb+1] < b);
            } else if (xa - xb == 1) {
                v += b < a ? 1 : -1;
                v += (a < p[xb-1]) - (b < p[xb-1]);
                v += (p[xa+1] < b) - (p[xa+1] < a);
            } else {
                v += (b < p[xa-1]) - (a < p[xa-1]);
                v += (p[xb+1] < a) - (p[xb+1] < b);
                v += (a < p[xb-1]) - (b < p[xb-1]);
                v += (p[xa+1] < b) - (p[xa+1] < a);
            }
            p[xa] = b;
            p[xb] = a;
            x[a] = xb;
            x[b] = xa;
        }
        printf("%d\n", v);
    }
}