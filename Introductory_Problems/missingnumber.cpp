#include <iostream>
using namespace std;
int main()
{
	cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
	long n,input,sum=0;
	cin>>n;
	// for (int i=0; i++<n-1;cin>>input,sum+=cin>>input);
	int i=n-1;
	while(i--){cin>>input; sum+=input;}
	cout<<n*(n+1)/2-sum;
}