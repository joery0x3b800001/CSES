#include <iostream>
using ll = long long;
#pragma GCC optimize("O3")
using namespace std;

ll readInt() {
	bool minus = false;
	ll result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	return (minus) ? -result : result;
}

int main() {
	ll tt, k, first, q, r, length;
	ios_base::sync_with_stdio(0);

	tt = readInt();

	while(tt--) {
		k = readInt();

		length = first = 1;

		while (k > 9 * first * length) {
			k -= 9 * first * length;
			length += 1;
			first *= 10;
		}
		q = (k - 1) / length;
		r = (k - 1) % length;

		printf("%c\n", to_string(first + q)[r]);
	}
}