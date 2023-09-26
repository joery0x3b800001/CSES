#include <cstdio>
#include <algorithm>
#define gc getchar_unlocked
#define pc putchar_unlocked
using namespace std;

void scan(int &angka)
{
	angka = 0;
	bool negative = false;
	char input = gc();
	while((input < '0') || (input > '9'))
	{
		if (input == '-')
			negative = true;
		input = gc();
	}

	while (input >= '0' && input <= '9')
	{
		angka = (angka << 3) + (angka << 1) + input - 48;
		input = gc();
	}

	if (negative)
		angka = -angka;
}

void print(int angka)
{
	char number[10];
	short i = 0;
	if (angka == 0)
	{
		pc('0');
		return;
	}

	while (angka > 0)
	{
		number[i++] = angka % 10 + '0';
		angka /= 10;
	}

	while (i--) 
		pc(number[i]);
}


const int MAX = 1e5;
int used[MAX];

int notUsed(int index)
{
	if (index < 0)
		return -1;
	else if (used[index] == -2)
	{
		used[index] = index - 1;
		return index;
	}
	else
	{
		used[index] = notUsed(used[index]);
		return used[index];
	}
}


int main() {
	int n,m;
	scan(n);
	scan(m);
	int arr[n];

	for (int i=0; i<n; i++)
	{
		scan(arr[i]);
		used[i] = -2;
	}

	sort(arr, arr+n);

	while (m--)
	{
		int t,index;
		scan(t);
		index = notUsed(upper_bound(arr, arr+n, t) - arr - 1);

		if (index >= 0)
		{
			print(arr[index]);
			pc('\n');
		}
		else
		{
			pc('-');
			pc('1');
			pc('\n');
		}
	}
	return 0;
}