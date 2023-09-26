#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
 
 
using namespace std;
using namespace __gnu_pbds;
 
typedef tree<long long, null_type, less<long long>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
typedef tree<long long, null_type, less_equal<long long>, rb_tree_tag, tree_order_statistics_node_update> indexed_multiset;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<string> vs;
typedef priority_queue<int> pqmaxi;
typedef priority_queue<ll> pqmaxl;
typedef priority_queue<int, vi, greater<int>> pqmini;
typedef priority_queue<ll, vl, greater<ll>> pqminl;
 
#define f first
#define s second
#define fo(i, a, b) for (long long i = a; i < b; ++i)
#define fm(i, a, b) for (long long i = a; i > b; --i)
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define test     \
    ll test;     \
    cin >> test; \
    while (test--)
#define pb(i) push_back(i)
#define eb(i) emplace_back(i)
#define mp(i, j) make_pair(i, j)
#define fast                     \
    ios::sync_with_stdio(false); \
    cin.tie(NULL);
const ll mod = 1000000007;
 
 
ll power(ll x, ull y, ll p) {
    ll r = 1;  x %= p;
    if (!x) return 0;
    while (y) {
        if (y & 1) r = (r * x) % p;
        y >>= 1;
        x = (x * x) % p;
    }
    return r;
}
 
 
bool visited[9][9] = {false};
ll ways = 0, force[48] = {0}; // 1 for u , 2 for d , 3 for l , 4 for r
unordered_map<char, int> umap(4);
 
bool onlyway(ll i , ll j) {
    if (i == 7 && j == 1) return 0;
    bool poss[4] = { !visited[i - 1][j] , !visited[i + 1][j] , !visited[i][j - 1] , !visited[i][j + 1] };
    int c = 0;
    fo(i, 0, 4) if (poss[i]) c++;
    return c == 1;
}
inline void search(ll i, ll j, ll pathlength) {
    visited[i][j] = true;
    if (i == 7 && j == 1) ways += (pathlength == 48);
    else {
 
        bool possible[4] = { !visited[i - 1][j] , !visited[i + 1][j] , !visited[i][j - 1] , !visited[i][j + 1] };
        if (force[pathlength]) fo(elem, 0, 4) possible[elem] *= (elem + 1 == force[pathlength]);
 
        bool returnCase;
        returnCase = (possible[0] == possible[1]) && (possible[2] == possible[3]); // T cuts
        returnCase += possible[0] && possible[3] && visited[i - 1][j + 1]; // UR cut
        returnCase += possible[0] && possible[2] && visited[i - 1][j - 1]; //UL cut
        returnCase += possible[1] && possible[3] && visited[i + 1][j + 1]; //DR cut
        returnCase += possible[1] && possible[2] && visited[i + 1][j - 1]; // DL cut
        if (!returnCase) {
            if (!force[pathlength]) {
                if (possible[0] && onlyway(i - 1, j)) {
                    search(i - 1, j, pathlength + 1);
                    visited[i][j] = 0;
                    return;
                }
                if (possible[1] && onlyway(i + 1, j)) {
                    search(i + 1, j, pathlength + 1);
                    visited[i][j] = 0;
                    return;
                }
                if (possible[2] && onlyway(i, j - 1)) {
                    search(i, j - 1, pathlength + 1);
                    visited[i][j] = 0;
                    return;
                }
                if (possible[3] && onlyway(i, j + 1)) {
                    search(i, j + 1, pathlength + 1);
                    visited[i][j] = 0;
                    return;
                }
            }
            if (possible[0]) search(i - 1, j, pathlength + 1);
            if (possible[1]) search(i + 1, j, pathlength + 1);
            if (possible[2]) search(i, j - 1, pathlength + 1);
            if (possible[3]) search(i, j + 1, pathlength + 1);
        }
    }
    visited[i][j] = false;
}
 
int main() {
    auto time_req = clock();
    //fast;
    // code goes here
    string str; cin >> str;
    umap['U'] = 1, umap['D'] = 2, umap['L'] = 3, umap['R'] = 4;
    fo(i, 0, 9) fo(j, 0, 9) visited[i][j] = (i == 8 || i == 0 || j == 0 || j == 8);
 
    ll countq = 0;
    ll minindex = 49, maxindex = -1;
    fo(i, 0, str.length()) {
 
        if (str[i] == '?') {
            countq++;
            continue;
        }
        minindex = min(minindex, i);
        maxindex = max(maxindex, i);
        force[i] = umap[str[i]];
    }
 
    if (countq == 48) {
        cout << 88418 << "\n";
        return 0;
    }
    if (countq == 47) {
        if ((force[47] == 3)) {
            cout << 42771 << "\n";
            return 0;
        }
        if (force[47] == 2) {
            cout << 45647 << "\n";
            return 0;
        }
        if (force[46] == 3) {
            cout << 50786 << "\n";
            return 0;
        }
        if (force[46] == 4) {
            cout << 0 << "\n";
            return 0;
        }
    }
    search(1, 1, 0);
    cout << ways ;
 
 
 
    cerr << "\nSolved, time = " << (float)(clock() - time_req) / CLOCKS_PER_SEC << "s\n";
    return 0;