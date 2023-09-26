#include <bits/stdc++.h>
#define maxN 200000
using namespace std;
const int BUF_SZ = 1<<19;
inline namespace Input {
char buf[BUF_SZ];
int pos;
int len;
char next_char() {
    if (pos == len) {
        pos = 0;
        len = (int)fread(buf, 1, BUF_SZ, stdin);
        if (!len) {
            return EOF;
        }
    }
    return buf[pos++];
}
 
int read_int() {
    int x;
    char ch;
    int sgn = 1;
    while (!isdigit(ch = next_char())) {
        if (ch == '-') {
            sgn = -1;
        }
    }
    x = ch - '0';
    while (isdigit(ch = next_char())) {
        x = x*10 + (ch - '0');
    }
    return x * sgn;
}
} // namespace Input
inline namespace Output {
char buf[BUF_SZ];
int pos;
 
void flush_out() {
    fwrite(buf, 1, pos, stdout);
    pos = 0;
}
 
void write_char(char c) {
    if (pos == BUF_SZ) {
        flush_out();
    }
    buf[pos++] = c;
}
 
void write_int(int x) {
    static char num_buf[100];
    if (x < 0) {
        write_char('-');
        x *= -1;
    }
    int len = 0;
    for (; x >= 10; x /= 10) {
        num_buf[len++] = (char)('0' + (x % 10));
    }
    write_char((char)('0' + x));
    while (len) {
        write_char(num_buf[--len]);
    }
    write_char('\n');
}
 
// auto-flush output when program exits
void init_output() { assert(atexit(flush_out) == 0); }
}
void setio(string name = "") { 
    ios::sync_with_stdio(false), cin.tie(nullptr); 
    if(name.length()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}
int buckets[80045][4][2];
int upd(int num, int pos){
    long long put = num*10002;
    if(put < 0) put = -put;
    int get = put%80045;
    for(int i = 0; i<4; i++) if(buckets[get][i][0] == num){
        int ret = buckets[get][i][1];
        buckets[get][i][1] = pos;
        return ret;
    }else if(buckets[get][i][0] == 0){
        buckets[get][i][0] = num;
        buckets[get][i][1] = pos;
        return -1;
    }
    return -1;
}
int main() {
    init_output();
    int N = read_int(), ans = 0, s = -1;
    for(int i = 0; i<N; i++){
        s = max(s, upd(read_int(), i));
        ans = max(ans, i-s);
    }
    write_int(ans);
}