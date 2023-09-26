#include <algorithm>
#include <cassert>
#include <stdio.h>
#include <unistd.h>
 
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long int;
// clang-format off
#define cond(a, b, c) ((a) ? (b) : (c))
#define break_if(a) {if ((a)) break;} 
#define exit_if(a) {if ((a)) return;}
// clang-format on
 
char chars[10]; // Max int = 2147483647
int digits = 0;
 
int pp = 0;
char bb[100 * 1000 * 100];
 
#define putchar_unlocked(ch) (bb[pp++] = (ch))
 
void print_int(int val)
{
 
  if ((val % 10) < 2 or val == 2)
  {
    digits = 0;
    do
    {
      chars[digits++] = ((val % 10) + '0');
      val /= 10;
    } while (val && digits < 10);
  }
  else
  {
    chars[0] = (val % 10) + '0';
  }
 
  int t = digits;
 
  while (t > 0)
  {
    putchar_unlocked(chars[--t]);
  }
  putchar_unlocked(' ');
}
 
int main()
{
  ios_base::sync_with_stdio(false);cin.tie(NULL);
  int n;
  cin >> n;
  assert(n >= 1 and n <= 1e6);
 
 
  if (n == 1)
    printf("1\n");
  else if (n == 2 or n == 3)
    printf("NO SOLUTION\n");
  else if (n >= 4)
  {
   
    for (int i{2}; i <= n; i += 2)
      print_int(i);
    for (int i{1}; i <= n; i += 2)
      print_int(i);
 
    fwrite_unlocked(bb, 1, pp, stdout);
  }
 
  return 0;
}