#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define ed << "\n";
#define el cout<<'\n';
#define rep(i,a,n,b) for(int i=a;i<=n;i+=b)
#define foru(i,a,n,b) for(int i=a;i<=n;i+=b)
#define ALL(s) s.begin(),s.end()
#define fi first
#define se second
#define mem(dp,a) memset(dp,a,sizeof dp)
#define ford(i,a,n,b) for(int i=a; i>=n; i-=b)
#define pb(x) push_back(x);
#define db(x) cerr << #x << " = " << x << endl;
#define A(a) abs(a)
#define SZ(x) ((int) (x.size()))
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define REP(i, a, b) for (int i = (a), _b = (b); i < _b; i++)
#define FOD(i,r,l) for(int i=r; i>=l; i--)
#define LT(x) (1LL << (x))
#define GB(x,i) ((x) >> (i) & 1)
#define SQ(a) (a)*(a)
#define pii pair<int,int>
#define int ll
// check if N is power of 2
bool ispow2(ll n) {
    return n && (n & -n) == n;
}
template <class T> inline bool minimize(T &a, const T &b) {
    return (a > b ? (a = b),1 : 0);
}
template <class T> inline bool maximize(T &a, const T &b) {
    return (a < b ? (a = b),1 : 0);
}
const ll MOD = 1e9 + 7;
 
void ADD(int &x,const int &y) {
    x += y;
    if (x >= MOD) x -= MOD;
}
const ll mod[] = {998244353,(int)1e9+7,987654323,(ll) 2e11 + 9, 1110111110111};
const int base[] = {31,311,331};
const ll INF = 1e18 + 7;
const int N = 1e6 + 20;
const int NP = 3e5 + 12;
const int NMAX =  5e4 + 23;
 
int cur_test ;
 
//struct Point {
//    int x,y;
//    Point (const int _x = 0, const int _y = 0) {
//        x = _x, y = _y ;
//    }
//    Point operator -(const Point &a) const {
//        return Point(x - a.x, y - a.y);
//    }
//    bool operator <(const Point &a) const {
//        return make_pair(x, y) < make_pair(a.x, a.y) ;
//    }
//} p[200005];
//
//ll Calc(Point a,Point b) {
//    return (ll) a.x * b.y - (ll) a.y * b.x;
//}
//
//int sig(Point a,Point b) {
//    ll t = Calc(a, b) ;
//    if(t < 0)
//        return - 1;
//    if(t > 0)
//        return 1;
//    return 0;
//}
//
//ll area(Point a, Point b, Point c) {
//    c = c - a;
//    b = b - a;
//    return A(b.x * c.y - b.y * c.x);
//}
//
//bool ccw(const Point &a, const Point &b, const Point &c) {
//    return sig(b - a, c - a) >= 0 ;
//}
//
//bool cw(const Point &a, const Point &b, const Point &c) {
//    return sig(b - a, c - a) <= 0 ;
//}
//
//
//void Convex_Hull() {
//    int up, down;
//    up = down = 0;
//    Point u[200005], d[200005];
//    Point v[200005];
//    int sz;
//
//    for(int i=1; i<=n; i++) {
//        while(up >= 2 && !cw(u[up-1], u[up], p[i])) up --;
//        while(down >= 2 && !ccw(d[down-1], d[down], p[i])) down --;
//        u[++ up] = d[++ down] = p[i];
//    }
//
//    cout << up + down - 2 << '\n' ;
// just for debug
//    FOR(i, 1, up) cout << u[i].x << ' ' << u[i].y ed
//    FOD(i, down - 1, 2) cout << d[i].x << ' ' << d[i].y ed
//
//
//    sz = 0 ;
//    FOR(i,1,up) v[++sz] = u[i];
//    FOD(i,down-2,2) v[++sz] = d[i];
//}
//
//int f[300003];
//int inf[300003];
//int mul(int a,int b) {
//    return 1LL * a * b % MOD ;
//}
 
//int pw(int a,int b){
//    if(b == 0)
//        return 1;
//    if(b == 1)
//        return a;
//    int t = pw(a, b / 2) ;
//    t = mul(t, t) ;
//    if(b & 1)
//        return mul(t, a);
//    return t;
//}
//
//int C(int n,int k){
//    return mul(f[n], mul(inf[n-k], inf[k])) ;
//}
 
 
#define int ll
int n, m;
int a[42];
int b[42];
int c[42];
vector <int> v;
map <int,int> mp;
int sum ;
 
void Implement() {
    cin >> n ;
    FOR(i ,1, n) cin >> a[i], sum += a[i];
 
    int each = n / 2;
 
    FOR(i ,1, each) b[i] = a[i];
    int sz = 0;
    FOR(i ,each+1, n) c[++ sz] = a[i];
 
    REP(mask, 0, LT(each)){
        ll s = 0;
        REP(i, 0, each) if(mask >> i & 1) s += b[i+1];
        v.push_back(s);
    }
 
    sort(ALL(v));
    REP(i , 0, SZ(v)) mp[2*v[i]] ++;
 
    v.resize(unique(ALL(v)) - v.begin());
 
    REP(i ,0, SZ(v)) v[i] = v[i] * 2;
 
    ll ans = 1e18;
    ll ways = 0 ;
 
    REP(mask, 1, LT(sz)){
        ll s = 0;
        ll best = 1e9 ;
        REP(i, 0, sz) if(mask >> i & 1) s += c[i+1];
        int r = upper_bound(ALL(v), sum - 2 * s) - v.begin();
 
        best = min(best, A(sum - 2 * s - v[r]));
 
        if(best == ans){
            ways += mp[v[r]] ;
        }else if(best < ans){
            ans = best;
            ways = mp[v[r]];
        }
        if(r == 0) continue;
 
//        if(ans == A(sum - 2 * s - v[r - 1])){
//            ways += mp[v[r-1]] ;
//            cerr << sum << ' ' << ans << ' ' << s ed
//        }else
        if(ans > A(sum - 2 * s - v[r - 1])){
            ans = A(sum - 2 * s - v[r - 1]);
            ways = mp[v[r-1]];
        }
 
//        if(r <= 1) continue;
//
//        if(ans == A(sum - 2 * s - v[r - 2])){
//            ways += mp[v[r-2]] ;
//        }else if(ans > A(sum - 2 * s - v[r - 2])){
//            ans = best;
//            ways = mp[v[r-2]];
//        }
 
    }
 
    cout << ans;
}
 
 
inline void fre(const bool &t,int test = 1) {
    ios_base :: sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
#define task "SETSEQ"
    if(fopen(task".inp","r")) {
        freopen(task".inp","r",stdin);
        freopen(task".out","w",stdout);
    }
 
#define task "a"
    if(fopen(task".inp","r")) {
        freopen(task".inp","r",stdin);
        freopen(task".out","w",stdout);
    }
 
    if(t) cin >> test;
    FOR(i,1,test) cur_test = i, Implement();
}
 
signed main() {
 
//    test :: sinh() ;
 
    fre(             0              );
 
    return 0;
}