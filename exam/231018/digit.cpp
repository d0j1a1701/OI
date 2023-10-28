#include <algorithm>
#include <iostream>
#include <cstring>
#include <map>
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
const long long mod = 1e9 + 7;
map<long long, long long> cnts{{1, 1}};
long long n, digits[1000010], suffix[1000010], dp[2][1000010];
long long prefix_total[1000010], prefix_dp1[1000010];
inline long long addmod(long long a, long long b) {
	return ((a + b) % mod + mod) % mod;
}
inline long long solve() {
	memset(dp, 0, sizeof(dp));
	memset(suffix, 0, sizeof(suffix));
	memset(prefix_total, 0, sizeof(prefix_total));
	memset(prefix_dp1, 0, sizeof(prefix_dp1));
	string S;
	long long D;
	io.read(S, D), n = S.size();
	transform(S.begin(), S.end(), digits, [](char c) {
		return c - '0';
	});
	long long d_remain = D;
	for (long long p : {
	            2, 5
	        }) {
		while (d_remain % p == 0) {
			d_remain /= p;
			cnts[p]++;
		}
	}
	long long l = max_element(cnts.begin(), cnts.end(), [](const auto & a, const auto & b) {
		return a.second < b.second;
	})->second;
	long long basis = 1;
	for (long long i = n - 1; i >= 0; --i) {
		suffix[i] = (suffix[i + 1] + digits[i] * basis) % d_remain;
		basis = basis * 10 % d_remain;
	}
	dp[0][0] = 1;
	long long accu_dp1 = 1, d_2_5 = D / d_remain;
	for (long long i = 1; i <= n; ++i) {
		dp[1][i] = accu_dp1;
		long long curr = 0, basis = 1;
		for (long long k = 1; k <= l; ++k) {
			if (i - k < 0)
				break;
			long long j = i - k;
			curr = (curr + digits[j] * basis) % d_2_5;
			if (k == l) {
				prefix_total[suffix[j]] = addmod(prefix_total[suffix[j]], addmod(dp[0][j], dp[1][j]));
				prefix_dp1[suffix[j]] = addmod(prefix_dp1[suffix[j]], dp[0][j]);
				if (curr == 0) {
					dp[0][i] = addmod(dp[0][i], prefix_total[suffix[i]]);
					dp[1][i] = addmod(dp[1][i], -prefix_dp1[suffix[i]]);
				}
				break;
			}
			if (curr == 0 && suffix[j] == suffix[i]) {
				dp[0][i] = addmod(dp[0][i], addmod(dp[0][j], dp[1][j]));
				dp[1][i] = addmod(dp[1][i], -dp[0][j]);
			}
			basis = basis * 10 % d_2_5;
		}
		accu_dp1 = addmod(accu_dp1, dp[0][i]);
	}
	return addmod(dp[0][n], dp[1][n]);
}
int main() {
	freopen("digit.in", "r", stdin);
	freopen("digit.out", "w", stdout);
	long long t = io.read();
	while(t--)	io.writeln(solve());
	return 0;
}
