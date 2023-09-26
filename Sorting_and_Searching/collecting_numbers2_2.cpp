#pragma GCC optimize("Ofast")
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
#ifdef ENABLE_DEBUG
#include <debug.h>
#else
#define DEBUG(...) do {} while (0)
#endif
 
using namespace std;
using namespace __gnu_pbds;
 
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using ulll = unsigned __int128;
 
template<typename T, size_t N> using ar = array<T, N>;
 
template<typename T, typename Cmp = less<T>>
using iset = tree<T, null_type, Cmp, rb_tree_tag,
		  tree_order_statistics_node_update, allocator<T>>;
 
#define REPSI(name, start, stop, step) for (ll name = start; name < (ll)stop; name += step)
#define REPS(name, start, stop) REPSI(name, start, stop, 1)
#define REP(name, stop) REPS(name, 0, stop)
 
#define RREPSI(name, start, stop, step) for (ll name = stop-1; name >= (ll)start; name -= step)
#define RREPS(name, start, stop) RREPSI(name, start, stop, 1)
#define RREP(name, stop) RREPS(name, 0, stop)
 
template<typename T> void cins(T &first) { cin >> first; }
template<typename T, typename... Ts> void cins(T &first, T &second, Ts&... rest) {
  cin >> first;
  cins(second, rest...);
}
 
#define GET(type, ...) type __VA_ARGS__; cins(__VA_ARGS__)
#define GETI(...) GET(int, __VA_ARGS__)
#define GETLL(...) GET(ll, __VA_ARGS__)
#define GETS(...) GET(string, __VA_ARGS__)
#define GETD(...) GET(double, __VA_ARGS__)
#define GETC(...) GET(char, __VA_ARGS__)
 
struct hsh {
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    x += FIXED_RANDOM;
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
};
 
const int mxN = 2e5;
int a[mxN], pos[mxN];
 
char IBUF[mxN*7*3+40], OBUF[mxN*7];
int IBUF_I = 0, OBUF_I = 0;
 
char _getchar() { return IBUF[IBUF_I++]; }
void _putchar(char c) { OBUF[OBUF_I++] = c; }
 
int read() {
  int x = 0;
  char c;
  while (c = _getchar(), c >= '0' && c <= '9')
    x = 10*x + c-'0';
  return x;
}
 
int main() {
  fread(IBUF, 1, sizeof(IBUF), stdin);
 
  int n = read(), m = read();
  REP(i, n) a[i] = read()-1;
  REP(i, n) pos[a[i]] = i;
  int ans = 1;
  REPS(i, 1, n) ans += pos[i]<pos[i-1];
 
  char BUF[18];
 
  DEBUG(ans);
 
  REP(mm, m) {
 
    int p1 = read()-1, p2 = read()-1;
 
    if (p1 != p2) {
      DEBUG(ans);
 
      if (a[p1] > 0) ans -= pos[a[p1]]<pos[a[p1]-1];
      if (a[p1] < n-1) ans -= pos[a[p1]]>pos[a[p1]+1];
      if (a[p2] > 0) ans -= pos[a[p2]]<pos[a[p2]-1];
      if (a[p2] < n-1) ans -= pos[a[p2]]>pos[a[p2]+1];
      DEBUG(ans);
 
      swap(a[p1], a[p2]);
      swap(pos[a[p1]], pos[a[p2]]);
 
      if (a[p1] > 0) ans += pos[a[p1]]<pos[a[p1]-1];
      if (a[p1] < n-1) ans += pos[a[p1]]>pos[a[p1]+1];
      if (a[p2] > 0) ans += pos[a[p2]]<pos[a[p2]-1];
      if (a[p2] < n-1) ans += pos[a[p2]]>pos[a[p2]+1];
      DEBUG(ans);
 
      if (abs(a[p1]-a[p2]) == 1) {
        if ((p1>p2) ^ (a[p1]>a[p2])) --ans;
        else ++ans;
      }
      DEBUG(ans);
      DEBUG("hmm");
    }
 
    int _ans = ans;
    int i = 18;
    do {
      BUF[--i] = _ans%10 + '0';
    } while (_ans /= 10);
    while (i < 18) _putchar(BUF[i++]);
    _putchar('\n');
 
  }
 
  OBUF[OBUF_I] = 0;
  fputs(OBUF, stdout);
}