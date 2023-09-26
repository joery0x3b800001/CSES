#include <bits/stdc++.h>
#define loop(i,a,b) for(int i=a;i<b;i++)
//#define local_test
using namespace std;
 
/* I/O template starts */
#ifdef local_test
/* For Windows */
inline int getchar_unlocked() { return getchar(); }
inline void putchar_unlocked(char _c) { putchar(_c); }
inline void fputs_unlocked(char* ans,FILE* strm) {fputs(ans,strm);}
inline void fread_unlocked(char* str,int bytes,int sz,FILE* strm) {fread(str,bytes,sz,strm);}
#endif
 
#define MAX_input_size 5000000
#define MAX_output_size 100
char output[MAX_output_size], input[MAX_input_size];
int input_ind = -1, output_ind = -1;
 
inline char gc(){
    input_ind++;
    return input[input_ind];
}
inline void GetInput(){
    fread_unlocked(input, 1, MAX_input_size, stdin);
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = gc()) < '-'){
        if(c == EOF) return EOF;
    }
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0; //判斷:正整數第一位or負號
    while((c = gc()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return true;
}
inline void PutInt(int x){
    static char c[30];
    int ind = 0, now = x;
    if(x == 0){
        output_ind++;
        output[output_ind] = '0';
        return;
    }
    if(x < 0){
        output_ind++;
        output[output_ind] = '-';
        now = -now;
    }
    while(now != 0){
        c[ind] = now % 10 + '0';
        ind++;
        now /= 10;
    }
    ind--;
    for(;ind >= 0; ind--){
        output_ind++;
        output[output_ind] = c[ind];
    }
    return;
}
inline void PutChar(char c){
    output_ind++;
    output[output_ind] = c;
    return;
}
inline void OutputFlush(){
    output[output_ind+1] = '\0';
    fputs_unlocked(output,stdout);
    output_ind = 0;
    return;
}
/* I/O template ends */
 
inline void radix_sort(int* a, int n){
    int cnt[32768] = {0};
    int tmpa[n];
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
    GetInput();
    int n, m, k;
    ReadInt(&n); ReadInt(&m); ReadInt(&k);
    int a[n], b[m];
    loop(i,0,n) ReadInt(&a[i]);
    radix_sort(a,n);
    loop(i,0,m) ReadInt(&b[i]);
    radix_sort(b,m);
    int i = 0, j = 0, ans = 0;
    while(i != n && j != m){
        if(abs(a[i] - b[j]) <= k){
            i++;
            j++;
            ans++;
            continue;
        }
        if(a[i] > b[j]) j++;
        else i++;
    }
    PutInt(ans);
    OutputFlush();
}