#include <cstdio>
#include<iostream>
#include <sstream>
#include <chrono>

std::chrono::time_point<std::chrono::steady_clock> hClock()
{
    return std::chrono::steady_clock::now();
}

std::uint32_t TimeDuration(std::chrono::time_point<std::chrono::steady_clock> Time)
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(hClock() - Time).count();
}


void Benchmark(const char* Name, std::string &str, void(*func)(std::string &str))
{
    auto time = hClock();
    for (int i = 0; i < 100; ++i)
    {
        func(str);
        str.clear();
    }
    std::cout<<Name<<" took: "<<TimeDuration(time) / 100<<" nano-seconds.\n";
}

void unlocked_bench(std::string &str)
{
    char c = '0';
    while((c = getchar_unlocked()) && (c != -1 && c != '\n' && c != '\r'))
    {
        str += c;
    }
}

void getchar_bench(std::string &str)
{
    char c = '0';
    while((c = getchar())  && (c != -1 && c != '\n' && c != '\r'))
    {
        str += c;
    }
}

void getline_bench(std::string &str)
{
    std::cin.getline(&str[0], str.size());
}

void scanf_bench(std::string &str)
{
    scanf("%[^\n]100s", &str[0]);
}

void fgets_bench(std::string &str)
{
    fgets(&str[0], str.size(), stdin);
}

void cinread_bench(std::string &str)
{
    std::cin.read(&str[0], str.size());
}

int main()
{
    std::string str;
    str.reserve(100);

    Benchmark("getchar_unlocked", str, unlocked_bench);
    Benchmark("getchar", str, getchar_bench);
    Benchmark("getline", str, getline_bench);
    Benchmark("scanf", str, scanf_bench);
    Benchmark("fgets", str, fgets_bench);
    Benchmark("cinread", str, cinread_bench);

    return 0;
}











inline long long read() {
    long long result = 0;
 
    while (true) {
        int c = getchar_unlocked();
 
        if (c < '0' || c > '9') {
            break;
        }
 
        result *= 10;
        result += c - '0';
    }
 
    return result;
}

















inline int static read(){
    int n = 0;
    char c = getchar();
    int k = 0;
    while (c < '0' || c > '9'){
        if (c == '-'){
            k = 1;
            c = getchar();
            break;
        }
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        n = (n * 10) + (c - '0');
        c = getchar();
    }
    return (k)? (-1) * n : n;
}














char *p1, *p2, buf[1<<20];
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1<<20, stdin), p1 == p2)? EOF : *p1++)












void out(unsigned long long x)
{
    char str[15];
    int pos = 0;
    do
    {
        str[pos++] = x % 10 + '0';
        x /= 10;
    } while (x);
    for (int i = pos - 1; i >= 0; i--)
        putchar_unlocked(str[i]);
    putchar_unlocked('\n');
}

























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










long long int read_int(){
    char r;
    bool start=false,neg=false;
    long long int ret=0;
    while(true){
        r=getchar();
        if((r-'0'<0 || r-'0'>9) && r!='-' && !start){
            continue;
        }
        if((r-'0'<0 || r-'0'>9) && r!='-' && start){
            break;
        }
        if(start)ret*=10;
        start=true;
        if(r=='-')neg=true;
        else ret+=r-'0';
    }
    return (!neg) ? ret : -ret;
}















int readInt () {
    bool minus = false;
    int result = 0;
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
    if (minus)
        return -result;
    else
        return result;
}




inline int ReadInt(int *x){
    static char c, neg;
    while((c = getchar()) < '-'){
        if(c == EOF) return EOF;
    }
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return true;
}



#include <bits/stdc++.h>

using namespace std;

int main() {
    // Original array
int arr[] = {3, 2, 6, 4};
// Size of original array
const int sz = static_cast<int>(sizeof arr / sizeof arr[0]);
// Array of pair {.first = item, .second = 1-based index
std::vector< pair<int, int> > vp(sz); // std::array if size is fixed
for(int i = 0; i < sz; ++i) vp[i] = make_pair(arr[i], i + 1);  /* Can be done in a more fancy way using std::transform + lambda */
// Sort the array, original array remains unchanged
std::sort(vp.begin(), vp.end());
// Print the result
for (int i=0; i<sz; ++i) cout << ' ' << vp[i].first;
cout << '\n';
for(int i = 0; i < sz; ++i) cout << ' ' << vp[i].second;
}
