#include <iostream>
#include <cstring>
using namespace std;
/* d0j1a_1701 FastIO full ver. 4.2 */
//#define FIO //缓存模式 请勿在交互题开启
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
	inline IO &flush() {
		fwrite(obuf, 1, pp - obuf, stdout);
		fflush(stdout);
		return *this;
	}
	IO() {
		p1 = buf, p2 = buf, pp = obuf;
	}
	~IO() {
		flush();
	}
#else
	int (*getchar)() = &::getchar;
	int (*putchar)(int) = &::putchar;
	inline IO &flush() {
		fflush(stdout);
		return *this;
	};
#endif
	string sep = " ";
	int k = 2;
	template < typename Tp, typename std::enable_if < std::is_integral<Tp>::value || std::is_same<Tp, __int128_t>::value >::type * = nullptr >
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
		while (isdigit(ch))		s = s * 10 + (ch ^ 48), ch = getchar();
		if(ch == EOF)	return false;
		if(ch == '.') {
			Tp eps = 0.1;
			ch = getchar();
			while (isdigit(ch))		s = s + (ch ^ 48) * eps, ch = getchar(), eps /= 10;
		}
		s *= f;
		return ch != EOF;
	}
	inline int read(char &c) {
		char ch = getchar();
		c = EOF;
		while(isspace(ch) && ch != EOF)     ch = getchar();
		if(ch != EOF) c = ch;
		return c != EOF;
	}
	inline int read(char *c) {
		char ch = getchar(), *s = c;
		while(isspace(ch) && ch != EOF)     ch = getchar();
		while(!isspace(ch) && ch != EOF)    *(c++) = ch, ch = getchar();
		*c = '\0';
		return s != c;
	}
	inline int read(string &s) {
		s.clear();
		char ch = getchar();
		while(isspace(ch) && ch != EOF)     ch = getchar();
		while(!isspace(ch) && ch != EOF)    s += ch, ch = getchar();
		return s.size() > 0;
	}
	inline int getline(char *c, const char &ed = '\n') {
		char ch = getchar(), *s = c;
		while(ch != ed && ch != EOF)		*(c++) = ch, ch = getchar();
		*c = '\0';
		return s != c;
	}
	inline int getline(string &s, const char &ed = '\n') {
		s.clear();
		char ch = getchar();
		while(ch != ed && ch != EOF)		s += ch, ch = getchar();
		return s.size() > 0;
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
		if(x > 1e18 || x < -1e18) {
			write("[Floating point overflow]");
			throw;
		}
		if(x < 0)	putchar('-'), x = -x;
		const static long long pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000, 10000000000000000, 100000000000000000, 100000000000000000, 100000000000000000};
		const auto &n = pow10[k];
		long long whole = (int)x;
		double tmp = (x - whole) * n;
		long long frac = tmp;
		double diff = tmp - frac;
		if (diff > 0.5) {
			++frac;
			if (frac >= n)	frac = 0, ++whole;
		} else if (diff == 0.5 && ((frac == 0U) || (frac & 1U))) ++frac;
		write(whole);
		if (k == 0U) {
			diff = x - (double)whole;
			if ((!(diff < 0.5) || (diff > 0.5)) && (whole & 1))
				++whole;
		} else {
			putchar('.');
			static char sta[20];
			int count = k, top = 0;
			while (frac) {
				sta[top++] = frac % 10 + '0';
				frac /= 10, count--;
			}
			while (count--) putchar('0');
			while (top) putchar(sta[--top]);
		}
		return *this;
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
	inline IO &writeWith(Tp x, const string &s = " ") {
		write(x), write(s);
		return *this;
	}
	inline IO &setsep(const string &s) {
		return sep = s, *this;
	}
	inline IO &setprec(const int &K) {
		return k = K, *this;
	}
} io;
int n, m, cnt, arr[110], dp[110][10010];
char s[110];
int main() {
	io.read(s + 1);
	n = strlen(s + 1);
	m = n * n / 2;
	for(int i = 1; i <= n; i++) arr[i] = s[i] - '0', cnt += !arr[i];
	memset(dp, 0x3f, sizeof(dp));
	dp[0][m] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = i; j >= 0; j--)
			for(int k = -m; k <= m; k++) {
				dp[j][k + m] = dp[j][k + m] + arr[i];
				if(j) dp[j][k + m] = min(dp[j][k + m], dp[j - 1][k + m + 2 * (i - j) - cnt] + (!arr[i]));
			}
	io.writeln(dp[n - cnt][m] == 0x3f3f3f3f ? -1 : dp[n - cnt][m] / 2);
	//system("pause");
	return 0;
}