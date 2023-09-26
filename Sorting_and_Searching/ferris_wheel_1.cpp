#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

inline uint64_t readInt() {
    uint64_t result = 0;
    int c;
    for (; (c = ::getchar()) < '0';);
    for (result = c - '0'; (c = ::getchar()) >= '0';) {
        result *= 10;
        result += c - '0';
    }
    return result;
}

int main() {
	uint64_t n, w;
	n = readInt(); w = readInt();

	uint64_t children[n];

	for (uint64_t i=0; i<n; i++) children[i] = readInt();

	sort(children, children+n);

	uint64_t left = 0;
	uint64_t right = n-1;
	uint64_t counter = 0;

	while (right > left) {
		if (children[right] + children[left] > w)
		{
			--right;
			++counter;
		} else
		{
			--right;
			++left;
			++counter;
		}
	}

	if (left == right) ++counter;
	cout << counter << '\n';
}