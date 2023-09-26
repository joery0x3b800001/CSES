#include <cstdio>
#include <vector>
#define gc getchar_unlocked
#define pc putchar_unlocked
#define int long long
using namespace std;
 
void scan(int &angka)
{
    angka = 0;
    bool negative = false;
    char input = gc();
    while ((input < '0') || (input > '9'))
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
    if (angka == 0)
    {
        pc('0');
        return;
    }
    else if (angka < 0)
    {
        pc('-');
        angka *= -1;
    }
 
    char number[20];
    short i = 0;
    while (angka > 0)
    {
        number[i++] = angka % 10 + '0';
        angka /= 10;
    }
    while (i--)
        pc(number[i]);
}
 
signed main()
{
    int n;
    scan(n);
    vector<int> arr;
 
    while (n--)
    {
        int k, max_size = arr.size();
        scan(k);
        if (max_size > 0 && k < arr.back())
        {
            int replaceIndex = -1;
            // get upper bound k in arr
            for (int i = 17; i >= 0; i--)
            {
                if (replaceIndex + (1 << i) < max_size && arr[replaceIndex + (1 << i)] <= k)
                    replaceIndex += (1 << i);
            }
            arr[++replaceIndex] = k;
        }
        else
            arr.push_back(k);
    }
 
    print(arr.size());
    pc('\n');
    return 0;
}