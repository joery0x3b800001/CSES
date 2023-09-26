#include <bits/stdc++.h>
#define loop(i,a,b) for(int i = a; i <b ; i++)
#define pb push_back
#define pii pair<int, int>
#define ff first
#define ss second
//#define local_test
#pragma GCC ("O3","unroll-loops")
using namespace std;
 
inline int ReadInt(int *x){
    static char c, neg;
    while((c = getchar()) < '-'){
        if(c == EOF) return EOF;
    }
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return true;
}
 
inline void radix_sort(pii* a, int n){
    int cnt[32768] = {0};
    vector<pii> tmpa(n);
    loop(i,0,n)
        cnt[a[i].ss & 32767]++;
    loop(i,1,32768)
        cnt[i] += cnt[i-1];
    int temp;
    for(int i = n-1; i >= 0; i--){
        temp = (a[i].ss) & 32767;
        cnt[temp]--;
        tmpa[cnt[temp]] = a[i];
    }
 
    int cnt2[32768] = {0};
    loop(i,0,n)
        cnt2[(tmpa[i].ss>>15) & 32767]++;
    loop(i,1,32768)
        cnt2[i] += cnt2[i-1];
 
    for(int i = n-1; i >= 0; i--){
        temp = (tmpa[i].ss>>15) & 32767;
        cnt2[temp]--;
        a[cnt2[temp]] = tmpa[i];
    }
    return;
}
 
int main(){
    #ifdef local_test
    freopen("test_input.txt","r",stdin);
    #endif // local_test
    int n;
    ReadInt(&n);
    pii a[n];
    loop(i,0,n){
        ReadInt(&a[i].ff);
        ReadInt(&a[i].ss);
    }
    radix_sort(a,n);
    int now = 0, ans = 0;
    loop(i,0,n){
        if(now <= a[i].ff){
            now = a[i].ss;
            ans ++;
        }
    }
    printf("%d",ans);
}
