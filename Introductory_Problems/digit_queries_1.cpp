#include <stdio.h>
 
int q = 0; long long int k;
 
long long int pow10(int N){
    long long int ten = 1;
    for (int i = 0; i < N; i++) {
        ten *= 10;
    }
    return ten;
}
 
int digit(long long int N){
    if (N < 10) {
        return (int)N;
    }
    else {
        long long int SUM = 9;
        int i = 2;
        while (N > SUM){
            SUM += (long long int)(9*i)*pow10(i-1);
            i++;
        }
        i--;
        SUM -= (long long int)(9*(i))*pow10(i-1);
        N -= SUM;
        return (int)((((N-1)/i + pow10(i-1)) / pow10(i - (N-1)%i - 1)) % 10);
    }
}
 
int main(){
 
    scanf("%d", &q);
 
    for (int i = 0; i < q; i++){
        scanf("%lld", &k);
        printf("%d\n", digit(k));
    }
}