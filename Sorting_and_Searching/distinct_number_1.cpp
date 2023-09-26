#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using ll = long long;

using namespace std;

inline ll readInt() {
    ll result = 0;
    int c;
    for (; (c = ::getchar()) < '0';);
    for (result = c - '0'; (c = ::getchar()) >= '0';) {
        result *= 10;
        result += c - '0';
    }
    return result;
}

ll turns;
int lo;
ll N;
vector<ll> vec;

int main() {
  // ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  N = readInt();

  for (ll i = 0; i < N; i++) {
    vec.push_back(readInt());
  }

  sort(vec.begin(), vec.end());

  for (ll i = 0; i < N; i++) {
    if (vec[i] == lo) {
      continue;
    } else {
      lo = vec[i];
      turns++;
    }
  }
  printf("%lld", turns);
}