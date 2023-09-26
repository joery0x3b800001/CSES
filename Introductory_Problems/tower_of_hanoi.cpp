#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

inline unsigned readUnsigned() {
    unsigned result = 0;
    int c;
    for (; (c = ::getchar()) < '0';);
    for (result = c - '0'; (c = ::getchar()) >= '0';) {
        result *= 10;
        result += c - '0';
    }
    return result;
}

void hanoi(unsigned n, char src, char aux, char dest) {
	if (n==1) {
		printf("%c %c\n", src, dest);
	} else {
		hanoi(n-1, src, dest, aux);
		hanoi(1, src, aux, dest);
		hanoi(n-1, aux, src, dest);
	}
}

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	char disks[3] = { '1', '2', '3' };

	unsigned n;
	n = readUnsigned();
	// scanf("%ld", &n);
	printf("%d\n", (1 << n)-1);
	hanoi(n, disks[0], disks[1], disks[2]);
}