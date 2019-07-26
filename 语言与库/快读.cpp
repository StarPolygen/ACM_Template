//快读快写 
//用于读写数 兼容负数 

//快读
template<typename T>inline void read(T &x)
{
    x=0;
    static int p;p=1;
    static char c;c=getchar();
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    x*=p;
}

//快写 
inline void write(int x)
{
     if(x < 0) putchar('-'),x = -x;
     if(x > 9) write(x / 10);
     putchar(x % 10 + '0');
}


//更全 用法就和cin 和 cout一样
#include<string>
#include<vector>
#include<regex>
#include<algorithm>
#include<random>
#include<map>
#include<array>
#include<set>
#include<deque>
#include<iomanip>
#include<sstream>
#include<stack>
#include<iostream>
#include<limits>
#include<bitset>
#include<list>
#include<queue>
#include<memory.h>
#include<unordered_map>
#include<functional>
using namespace std;
struct ioss {
#define endl '\n'
    static const int LEN = 20000000;
    char obuf[LEN], *oh = obuf;
    std::streambuf *fb;
    ioss()
    {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        fb = cout.rdbuf();
    }
    inline char gc() {
 
        static char buf[LEN], *s, *t, buf2[LEN];
        return (s == t) && (t = (s = buf) + fread(buf, 1, LEN, stdin)), s == t ? -1 : *s++;
    }
    inline ioss & operator >> (long long&x) {
        static char ch, sgn, *p;
        ch = gc(), sgn = 0;
        for (; !isdigit(ch); ch = gc()) { if (ch == -1)return *this; sgn |= ch == '-'; }
        for (x = 0; isdigit(ch); ch = gc())x = x * 10 + (ch^'0');
        sgn && (x = -x); return *this;
    }
    inline ioss & operator >> (int &x) {
        static char ch, sgn, *p;
        ch = gc(), sgn = 0;
        for (; !isdigit(ch); ch = gc()) { if (ch == -1)return *this; sgn |= ch == '-'; }
        for (x = 0; isdigit(ch); ch = gc())x = x * 10 + (ch^'0');
        sgn && (x = -x); return *this;
    }
    inline ioss & operator >> (char&x)
    {
        static char ch;
        for (; !isalpha(ch); ch = gc())
        {
            if (ch == -1)return *this;
        }
        x = ch;
        return *this;
    }
    inline ioss & operator >> (string &x)
    {
        static char ch, *p, buf2[LEN];
        for (; !isalpha(ch) && !isdigit(ch); ch = gc())
            if (ch == -1)return *this;
        p = buf2;
        for (; isalpha(ch)|| isdigit(ch); ch = gc())
            *p = ch, p++;
        *p = '\0';
        x = buf2;
        return *this;
    }
    inline ioss & operator <<(string &c)
    {
        for (auto &p : c)
            this->operator<<(p);
        return *this;
    }
    inline ioss & operator <<(const char *c)
    {
        while (*c != '\0')
        {
            this->operator<<(*c);
            c++;
        }
        return *this;
    }
    inline ioss & operator <<(const char &c) {
        oh == obuf + LEN ? (fb->sputn(obuf, LEN), oh = obuf) : 0;
        *oh++ = c;
        return *this;
    }
    inline ioss & operator <<(int x) {
        static int buf[30], cnt;
        if (x < 0)
            this->operator<<('-'),x=-x;
        if (x == 0)
            this->operator<<('0');
        for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 | 48;
        while (cnt) this->operator<<((char)buf[cnt--]);
        return *this;
    }
    inline ioss & operator <<(long long x) {
        static int buf[30], cnt;
        if (x < 0)
            this->operator<<('-'), x = -x;
        if (x == 0)
            this->operator<<('0');
        for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 | 48;
        while (cnt) this->operator<<((char)buf[cnt--]);
        return *this;
    }
    ~ioss()
    {
        fb->sputn(obuf, oh - obuf);
    }
} io; 