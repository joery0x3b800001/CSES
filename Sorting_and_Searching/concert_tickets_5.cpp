#include <bits/stdc++.h>
using namespace std;
 
const char digits[] =
    "00010203040506070809101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";
 
#define pc(x) putchar_unlocked(x);
inline void writeInt(int n) {
    char buf[32];
    int idx = 0;
 
    if (n == 0) {
        pc('0');
        return;
    } else if(n==-1) {
        pc('-');
        pc('1');
        return;
    }
 
    while (n >= 100) {
        int val = n % 100;
        buf[idx++] = digits[val * 2 + 1];
        buf[idx++] = digits[val * 2];
        n /= 100;
    }
 
    while (n) {
        buf[idx++] = n % 10 + '0';
        n /= 10;
    }
 
    while (idx--) {
        pc(buf[idx]);
    }
}
 
 
#define gc() getchar_unlocked()
 
inline void fs(int &number) {
    int c = gc();
    while (c == ' ' || c == 10)
        c = gc();
 
    number = 0;
    while (c >= '0' && c <= '9') {
        number = number * 10 + c - '0';
        c = gc();
    }
}
 
 
struct Dsu {
    vector<int> p;
/* initializes each (0..size-1) to single set */
    Dsu(int size) {
        p.resize(size);
        for(int i=0; i<size; i++)
            p[i]=i;
    }
 
/* finds set representative for member v */
    int find_set(int v) {
        if (v == p[v])
            return v;
        return p[v] = find_set(p[v]);
    }
 
/* makes v a single set, removes it from other set if contained there. */
    void make_set(int v) {
        p[v] = v;
    }
 
/* combines the sets of two members. 
 * Use the bigger set as param a for optimized performance.  */
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
            p[b] = a;
    }
};


int main() {
    int n,m;
    fs(n);
    fs(m);

    Dsu dsu(n+1);

    vector<int> tick(n);
    for (int i=0; i<n; i++)
        fs(tick[i]);

    sort(tick.begin(), tick.end(), greater<int>());

    vector<bool> done(n);
    for (int i=0; i<m; i++) {
        int cust;
        fs(cust);

        int result = -1;
        auto it = lower_bound(tick.begin(), tick.end(), cust, greater<int>());
        if (it != tick.end()) {
            int idx = it - tick.begin();
            int jidx = dsu.find_set(idx);

            while (jidx < n && done[jidx]) {
                dsu.union_sets(jidx + 1, jidx);
                jidx++;
            }

            if (jidx < n) {
                result = tick[jidx];
                done[jidx] = true;
            }
        }

        writeInt(result);
        pc('\n');
    }
}