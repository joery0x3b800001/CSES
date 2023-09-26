#include<bits/stdc++.h>
using namespace std;
 
typedef int ll;
inline ll rlolo(){
	ll t = 0;
	char c;
	while((c=getchar_unlocked())!=' '&&c!='\0'&&c!='\n')t=t*10+c-48;
	return t;
}
 
int main(){
	int n = rlolo(), x = rlolo();
 
	int a[n];
	for(int i = 0; i < n; i++){
		a[i] = rlolo();
	}
 
	int b[n];
	memcpy(b, a, sizeof(int) * n);
 
	sort(a, a+n);
 
	int s = 0, e = n-1;
	while(s < e){
		int t = a[s] + a[e];
		if(t > x){
			e--;
		} else if(t < x){
			s++;
		} else {
			int bp;
			int spos = -1;
			for(int i = 0; i < n; i++){
				if(b[i] ==a[s]){
					spos = i;
					break;
				}
			}
			for(int i = 0; i < n; i++){
				if(b[i] == a[e] && i != spos){
					bp = i+1;
					break;
				}
			}
			printf("%d %d", spos+1, bp);
			exit(0);
		}
	}
	printf("IMPOSSIBLE");
}