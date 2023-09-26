#include <bits/stdc++.h>
#define loop(i,a,b) for(int i=a;i<b;i++)
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
 
inline void radix_sort(int* a, int n){
    int cnt[32768] = {0};
    vector<int> tmpa(n);
    loop(i,0,n)
        cnt[a[i] & 32767]++;
    loop(i,1,32768)
        cnt[i] += cnt[i-1];
    int temp;
    for(int i = n-1; i >= 0; i--){
        temp = a[i] & 32767;
        cnt[temp]--;
        tmpa[cnt[temp]] = a[i];
    }
 
    int cnt2[32768] = {0};
    loop(i,0,n)
        cnt2[(tmpa[i]>>15) & 32767]++;
    loop(i,1,32768)
        cnt2[i] += cnt2[i-1];
 
    for(int i = n-1; i >= 0; i--){
        temp = (tmpa[i]>>15) & 32767;
        cnt2[temp]--;
        a[cnt2[temp]] = tmpa[i];
    }
    return;
}
 
int main(){
    int n;
    ReadInt(&n);
    int a[n];
    loop(i,0,n){
        ReadInt(&a[i]);
    }
    radix_sort(a,n);
    long long now = 0, ans = -1;
    loop(i,0,n){
        if(now +1 < a[i]){
            ans = now +1;
            break;
        }
        else{
            now += a[i];
        }
    }
    if(ans != -1)
        printf("%lld",ans);
    else
        printf("%lld",now +1);
    return 0;