#include <iostream>

using namespace std;

int main() {
	cin.tie(0); cout.tie(0);ios_base::sync_with_stdio(0);
	string str;
	cin>>str;

	size_t max=1,i=0,j=0,n=str.length();
	for (i=0, j=0; i<n-1; i=j) {
		for (j=i+1; j<n && str[j]==str[i]; j++);
		if (j-i>max) {
			max=j-i;
		}
	}
	cout<<max;
}