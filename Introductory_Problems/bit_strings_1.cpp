#include<bits/stdc++.h>
#define pb emplace_back
#define fo(i,a,b) for(int i=(a);i<(b);i++)
#define dfo(i,a,b) for(int i=(a);i>=(b);i--)
#define vi vector<int>
#define vll vector<long long>
#define fi first
#define sc second
//#define MT 1
typedef long long ll;
using namespace std;
 
const int Nmx=1000000005, mod=1000000000+7, INF=INT_MAX-1;
 
 
 
//logarithm
/*
int LOG[Nmx];
 
void calc_log(){
	LOG[1]=0;
	for(int i=2;i<Nmx;i++){
		LOG[i]=LOG[i/2]+1;
	}
}
*/
 
//number theory func
/*
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
int lcm(int a,int b){
	return a*b/gcd(a,b);
}
*/
 
 
//mod actions
 
ll add_mod(ll a,ll b){ return ((a%mod)+(b%mod))%mod; }
ll multi_mod(ll a,ll b){ return ((a%mod)*(b%mod))%mod; }
ll sub_mod(ll a,ll b,int m){ return ((a-b)%mod+mod)%mod; }
 
ll powr(ll a,int b){
	ll result=1;
	while(b>0){
		if(b%2==1)result =(result*a)%mod;
		a=(a*a)%mod;
		b/=2;
	}
	return result%mod;
}
 
ll div_mod(ll a,ll b,int m){ return  (a*powr(b,mod-2))%mod; } //euler's theorem
 
 
 
//factorial
/*
ll fact[Nmx],inv[Nmx];
 
void calc_fact(){
	ll i=1;
	fact[0]=1;
	while(i<Nmx){
		fact[i]=(fact[i-1]*i)%mod;
		i++;
	}
	inv[Nmx-1]=pow(fact[Nmx-1],mod-2); 
	for(ll j=Nmx-1;j>0;j--){
		inv[j-1]=multi_mod(inv[j],j,mod);
	}
}
*/
 
 
// combinatorics
/*
ll C(ll k,ll n){
	ll dv=multi_mod(fact[k],fact[n-k],mod);
	return div_mod(fact[n],dv,mod);
}
 
ll P(ll k,ll n){
	return div_mod(fact[n],fact[n-k],mod);
}
*/
 
 
//combinatorics including inverses
/*
ll C(ll k,ll n){
	return ((fact[n]*inv[k])%mod*inv[n-k])%mod;
}
ll P(ll k,ll n){
	return (fact[n]*inv(n-k))%mod;
}
*/
 
 
//power
/*
ll pow(ll a,int b){
	ll result=1;
	while(b>0){
		if(b%2==1)result *=a;
		a*=a;
		b/=2;
	}
	return result;
}
*/
 
 
//binary serch less than or equal (n shi atvla iwyeba 1 indexidan)
/*
int bn_srch(vector<int>&a,int k,int &n){
	int l=1,r=n,mid=(l+r)/2,anss=0;
	while(l<=r){
		mid=(l+r)/2;
		if(a[mid]<=k){l=mid+1;anss=mid;}
		else if(a[mid]>k){r=mid-1;}
	}
	return anss; 
}
*/
 
 
//eratostenes saceri
/*
int erat[Nmx]; vi pr;
void eratostene(){
	erat[1]=1; 
	for(ll i=2;i<Nmx;i++){
		if(erat[i]==0){
			erat[i]=i; pr.pb(i);
			for(ll j=i*i;j<Nmx;j=j+i){
				if(erat[j]==0)erat[j]=i;
			}
		}
	}
}
*/
 
 
//factors ~O(nlogn) push_back anelebs, ricxvs ar aqvs log n ze meti gamyofi
/*
vector<ll>factors[Nmx];
 
void calc_factors(){
	for(int i=1;i<Nmx;i++){
		for(int j=i;j<Nmx;j+=i){
			factors[j].pb(i);
		}
	}
}
*/
 
 
void solve(){
	int n;
	cin>>n;
	int pr=2;
	pr = powr(pr,n);
	cout<<pr<<'\n';
}
 
 
 
#ifdef MT
void tsolve(){
	int tt;
	cin>>tt;
	while(tt--){
		solve();
	}
}
#else
void tsolve(){
	solve();
}
#endif
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	tsolve();
}