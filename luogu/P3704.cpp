#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
/* d0j1a_1701 FastIO full ver. 3.6 */
#define FIO //开启加速模式 将不能使用键盘读入
struct IO {
#ifdef FIO
	const static int BUFSIZE = 1 << 20;
	char buf[BUFSIZE], obuf[BUFSIZE], *p1, *p2, *pp;
	inline char getchar() {
		return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, BUFSIZE, stdin), p1 == p2) ? EOF : *p1++);
	}
	inline void putchar(char x) {
		((pp - obuf == BUFSIZE && (fwrite(obuf, 1, BUFSIZE, stdout), pp = obuf)), *pp = x, pp++);
	}
	inline void flush() {
		fwrite(obuf, 1, pp - obuf, stdout);
	}
	IO() {
		p1 = buf, p2 = buf, pp = obuf;
	}
	~IO() {
		fwrite(obuf, 1, pp - obuf, stdout);
	}
#else
	int (*getchar)() = &::getchar;
	int (*putchar)(int) = &::putchar;
	inline void flush() {};
#endif
	string sep = " ";
	int k = 2;
	template<typename Tp, typename enable_if<is_integral<Tp>::value>::type * = nullptr>
	inline int read(Tp &s) {
		int f = 1;
		char ch = getchar();
		s = 0;
		while (!isdigit(ch) && ch != EOF)	f = (ch == '-' ? -1 : 1), ch = getchar();
		while (isdigit(ch))		s = s * 10 + (ch ^ 48), ch = getchar();
		s *= f;
		return ch != EOF;
	}
	template<typename Tp, typename enable_if<is_floating_point<Tp>::value>::type * = nullptr>
	inline int read(Tp &s) {
		int f = 1;
		char ch = getchar();
		s = 0;
		while (!isdigit(ch) && ch != EOF && ch != '.')	f = (ch == '-' ? -1 : 1), ch = getchar();
		while (isdigit(ch))	s = s * 10 + (ch ^ 48), ch = getchar();
		if(ch == EOF)	return false;
		if(ch == '.') {
			Tp eps = 0.1;
			ch = getchar();
			while (isdigit(ch))	s = s + (ch ^ 48) * eps, ch = getchar(), eps /= 10;
		}
		s *= f;
		return ch != EOF;
	}
	inline int read(char &c) {
		char ch = getchar();
		while(isspace(ch) && ch != EOF)     ch = getchar();
		if(ch != EOF) c = ch;
		return ch != EOF;
	}
	inline int read(char *c) {
		char ch = getchar();
		while(isspace(ch) && ch != EOF)     ch = getchar();
		while(!isspace(ch) && ch != EOF)    *(c++) = ch, ch = getchar();
		return ch != EOF;
	}
	inline int read(string &s) {
		s.clear();
		char ch = getchar();
		while(isspace(ch) && ch != EOF)     ch = getchar();
		while(!isspace(ch) && ch != EOF)    s += ch, ch = getchar();
		return ch != EOF;
	}
	inline int getline(char *c, const char &ed = '\n') {
		char ch = getchar();
		while(ch != ed && ch != EOF)	*(c++) = ch, ch = getchar();
		return ch != EOF;
	}
	inline int getline(string &s, const char &ed = '\n') {
		s.clear();
		char ch = getchar();
		while(ch != ed && ch != EOF)	s += ch, ch = getchar();
		return ch != EOF;
	}
	template<typename Tp = int>
	inline Tp read() {
		Tp x;
		read(x);
		return x;
	}
	template<typename Tp, typename... Ts>
	int read(Tp &x, Ts &...val) {
		return read(x) && read(val...);
	}
	template<typename Tp, typename enable_if<is_integral<Tp>::value>::type * = nullptr>
	IO & write(Tp x) {
		if (x < 0)	putchar('-'), x = -x;
		static char sta[20];
		int top = 0;
		do sta[top++] = x % 10 + '0', x /= 10;
		while (x);
		while (top)
			putchar(sta[--top]);
		return *this;
	}
	inline IO &write(const string &str) {
		for(char ch : str)    putchar(ch);
		return *this;
	}
	inline IO &write(const char *str) {
		while(*str != '\0')	putchar(*(str++));
		return *this;
	}
	inline IO &write(char *str) {
		return write((const char *)str);
	}
	inline IO &write(const char &ch) {
		return putchar(ch), *this;
	}
	template<typename Tp, typename enable_if<is_floating_point<Tp>::value>::type * = nullptr>inline IO & write(Tp x) {
		const static long long pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000, 10000000000000000, 100000000000000000, 100000000000000000, 100000000000000000};
		const auto &n = pow10[k];
		if(x == 0) {
			putchar('0'), putchar('.');
			for(int i = 1; i <= k; ++i)	putchar('0');
			return *this;
		}
		if(x < 0)   putchar('-'), x = -x;
		long long d = (long long)(x + 1e-12), y = (long long)(x * n + 0.5);
		write(d), putchar('.');
		static char sta[20];
		int top = 0;
		for(; top < k; y /= 10) sta[top++] = y % 10 ^ 48;
		while(top)  putchar(sta[--top]);
		return*this;
	}
	template<typename Tp, typename... Ts>
	inline IO &write(Tp x, Ts... val) {
		write(x);
		write(sep);
		write(val...);
		return *this;
	}
	template<typename... Ts>
	inline IO &writeln(Ts... val) {
		write(val...);
		putchar('\n');
		return *this;
	}
	inline IO &writeln(void) {
		putchar('\n');
		return *this;
	}
	template<typename Tp>
	inline IO &writeWith(Tp x, const string &s) {
		write(x), write(s);
		return *this;
	}
	inline IO &setsep(const string &s) {
		return sep = s, *this;
	}
	inline IO &setprecision(const int &K) {
		return k = K, *this;
	}
} io;
const int mod = 1000000007;
int s[1000010], invs[1000010];
int m, n, t, p[1000010], prime[100000], mu[1000010], cnt, nn[1005], mm[1005], sf[1000010];
inline int qpow(int a, int b) {
	int ans = 1;
	for(; b; b >>= 1, a = 1ll * a * a % mod)
		if(b & 1)ans = 1ll * ans * a % mod;
	return ans;
}
void make(int n) {
	mu[1] = p[1] = invs[0] = s[1] = invs[1] = sf[1] = 1;
	for(int i = 2; i <= n; i++) {
		s[i] = (s[i - 1] + s[i - 2]) % mod, sf[i] = 1ll * sf[i - 1] * s[i] % mod;
		if(!p[i])prime[++cnt] = i, mu[i] = -1;
		for(int j = 1, x; j <= cnt && (x = i * prime[j]) <= n; j++) {
			p[x] = 1;
			if(i % prime[j])mu[x] = -mu[i];
			else break;
		}
	}
	int sis = qpow(sf[n], mod - 2);
	for(int i = n; i >= 2; i--)invs[i] = 1ll * sis * sf[i - 1] % mod, sis = 1ll * sis * s[i] % mod;
	for(int i = 1; i <= cnt; i++) {
		for(int jj = n / prime[i], j = jj * prime[i]; jj >= 1; jj--, j = jj * prime[i]) {
			s[j] = 1LL * s[j] * invs[jj] % mod;
			invs[j] = 1ll * invs[j] * s[jj] % mod;
		}
	}
	for(int i = 2; i <= n; i++)s[i] = 1ll * s[i] * s[i - 1] % mod, invs[i] = 1ll * invs[i] * invs[i - 1] % mod;;
}
int main() {
	io.read(t);
	int maxn = 0;
	for(int i = 1; i <= t; i++) io.read(nn[i], mm[i]), maxn = max(maxn, min(nn[i], mm[i]));
	make(maxn);
	for(int TTT = 1; TTT <= t; TTT++) {
		int n = nn[TTT], m = mm[TTT];
		if(n > m)swap(n, m);
		int ans = 1;
		int i = 1, lt = sqrt(n);
		for(; i <= lt; i++)
			ans = (1ll * ans * qpow(1ll * s[i] * invs[i - 1] % mod, 1ll * (n / i) * (m / i) % (mod - 1))) % mod;
		for(; i <= n; i = lt + 1) {
			lt = min(n / (n / i), m / (m / i));
			ans = (1ll * ans * qpow(1ll * s[lt] * invs[i - 1] % mod, (n / i) * (m / i))) % mod;
		}
		io.writeln(ans);
	}
}
