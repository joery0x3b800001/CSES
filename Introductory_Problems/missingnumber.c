#include <stdio.h>

int main()
{
	long n,input,sum=0;
	scanf("%ld", &n);
	for (int i=n-1; i--!=0;) {
		scanf("%ld", &input);
		sum+=input;
	}
	printf("%ld", n*(n+1)/2-sum);
}