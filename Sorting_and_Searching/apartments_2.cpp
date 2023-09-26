#include <bits/stdc++.h>
#define loop(i,a,b) for(int i=a;i<b;i++)
using namespace std;
 
inline int readInt() {
    int result = 0;
    int c;
    for (; (c = ::getchar()) < '0';);
    for (result = c - '0'; (c = ::getchar()) >= '0';) {
        result *= 10;
        result += c - '0';
    }
    return result;
}

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

int main() {
	int n,m,k;
	n = readInt(); m = readInt(); k = readInt();
	int a[n], b[m];
	loop(i,0,n) a[i] = readInt();
    radix_sort(a, n);
	loop(i,0,m) b[i] = readInt();
    radix_sort(b, m);
	int i = 0, j = 0, result = 0;
	while (i != n && j != m) {
		if (abs(a[i] - b[j]) <= k) {
			i++;
			j++;
			result++;
			continue;
		}
		if ( a[i] > b[j]) j++;
		else i++;
	}
	cout << result;
}