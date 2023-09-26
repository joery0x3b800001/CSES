#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
 
char buf[1288902];
ull idx = 0;
 
ull read_int() {
    ull ret = 0;
    while (buf[idx] & 16) {
        char n = buf[idx] & 15;
        ret *= 5;
        ret <<= 1;
        ret += n;
        idx++;
    }
    idx++;
    return ret;
}
 
int main() {
    read(0, buf, 1288902);
    ull n = read_int();
    ull arr[200001];
    ull ans = 1;
    for (ull i = 0; i < n; i++)
        arr[read_int()] = i;
    for (ull i = 2; i < n + 1; i++)
        ans += (arr[i] < arr[i-1]);
    cout << ans;
}
