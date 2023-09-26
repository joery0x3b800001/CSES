#include <bits/stdc++.h>

#define mx 200005
using ll = long long;
using namespace std;

int main() {
	ll n;cin>>n;
	 ll a[mx];
	 for(ll i=0;i<n;++i)
	 {
	   cin>>a[i];
	 }
	 map<ll,ll>mp;
	 ll result=0;
	 for(ll i=0,j=0;i<n;++i)
	 {
	    j=max(mp[a[i]],j);
	    result=max(result,i-j+1);
	    mp[a[i]]=i+1;
	 }
	 cout<<result<<"\n";   
}