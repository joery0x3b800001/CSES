#include <ctype.h>
#include <stdint.h>
#include <iostream>

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

int main() {
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    unsigned N;
    if (scanf("%u", &N) != 1) return 1;
    unsigned long long turns = 0;
    unsigned lo = 0;
    for (unsigned i = 0; i<N; i++) {
        unsigned x = readUnsigned();
        if (x<lo) {
            turns += lo - x;
        } else {
            lo = x;
        }
    }
    printf("%llu\n", turns);
}