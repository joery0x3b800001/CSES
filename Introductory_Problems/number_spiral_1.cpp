#include <iostream>
#include <cmath>
 
using ll = long long;
 
void solve()
{
    ll x{}, y{};
    std::cin >> x >> y;
    if (x > y)
    {
        if (x % 2)
        {
            std::cout << (x - 1) * (x - 1) + y;
        }
        else
        {
            std::cout << x * x + 1 - y;
        }
    }
    else
    {
        if (y % 2)
        {
            std::cout << y * y + 1 - x;
        }
        else
        {
            std::cout << (y - 1) * (y - 1) + x;
        }
    }
 
    std::cout << '\n';
}
 
int main()
{
    ll t{};
    std::cin >> t;
    while (t--)
    {
        solve();
    }
 
    return 0;
}