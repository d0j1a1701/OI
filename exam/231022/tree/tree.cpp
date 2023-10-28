#include <iostream>
#include <cstring>
using namespace std;
/* d0j1a_1701 FastIO full ver. 4.2 */
#define FIO //����ģʽ �����ڽ����⿪��
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
		while(!isdigit(ch) && ch != EOF)	f = (ch == '-' ? -1 : 1), ch = getchar();
		while(isdigit(ch))		s = s * 10 + (ch ^ 48), ch = getchar();
		s *= f;
		return ch != EOF;
	}
	template<typename Tp, typename enable_if<is_floating_point<Tp>::value>::type * = nullptr>
	inline int read(Tp &s) {
		int f = 1;
		char ch = getchar();
		s = 0;
		while(!isdigit(ch) && ch != EOF && ch != '.')	f = (ch == '-' ? -1 : 1), ch = getchar();
		while(isdigit(ch))		s = s * 10 + (ch ^ 48), ch = getchar();
		if(ch == EOF)	return false;
		if(ch == '.') {
			Tp eps = 0.1;
			ch = getchar();
			while(isdigit(ch))		s = s + (ch ^ 48) * eps, ch = getchar(), eps /= 10;
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
		if(x < 0)	putchar('-'), x = -x;
		static char sta[20];
		int top = 0;
		do sta[top++] = x % 10 + '0', x /= 10;
		while(x);
		while(top)
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
		if(diff > 0.5) {
			++frac;
			if(frac >= n)	frac = 0, ++whole;
		} else if(diff == 0.5 && ((frac == 0U) || (frac & 1U))) ++frac;
		write(whole);
		if(k == 0U) {
			diff = x - (double)whole;
			if((!(diff < 0.5) || (diff > 0.5)) && (whole & 1))
				++whole;
		} else {
			putchar('.');
			static char sta[20];
			int count = k, top = 0;
			while(frac) {
				sta[top++] = frac % 10 + '0';
				frac /= 10, count--;
			}
			while(count--) putchar('0');
			while(top) putchar(sta[--top]);
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
const long long mod = 1000000007;
long long tid, t, n, l[310], r[310], dp[2][310][310];
int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	io.read(tid, t);
	while(t--) {
		io.read(n);
		for(int i = 1; i <= n; i++) io.read(l[i], r[i]);
		memset(dp[0], 0, sizeof(dp[0]));
		dp[0][0][0] = 1;
		for(int i = 1; i <= n; i++) {
			memset(dp[i & 1], 0, sizeof(dp[i & 1]));
			for(int j = 0; j < i; j++)
				for(int k = 0; k <= n; k++) {
					if(!dp[(i & 1) ^ 1][j][k]) continue;
					if(l[i] == 0) {
						dp[i & 1][j + 1][k] = (dp[i & 1][j + 1][k] + dp[(i & 1) ^ 1][j][k]) % mod;
						dp[i & 1][j][k - 1] = (dp[i & 1][j][k - 1] + dp[(i & 1) ^ 1][j][k] * k * (!!k) % mod) % mod;
					}
					if(l[i] <= 1 && r[i] >= 1) {
						dp[i & 1][j + 1][k + 1] = (dp[i & 1][j + 1][k + 1] + 2 * dp[(i & 1) ^ 1][j][k] % mod) % mod;
						dp[i & 1][j][k] = (dp[i & 1][j][k] + 2 * dp[(i & 1) ^ 1][j][k] * k % mod) % mod;
					}
					if(r[i] == 2) {
						dp[i & 1][j + 1][k + 2] = (dp[i & 1][j + 1][k + 2] + dp[(i & 1) ^ 1][j][k]) % mod;
						dp[i & 1][j][k + 1] = (dp[i & 1][j][k + 1] + dp[(i & 1) ^ 1][j][k] * k % mod) % mod;
						dp[i & 1][j][k + 1] = (dp[i & 1][j][k + 1] + 2 * dp[(i & 1) ^ 1][j][k] * j % mod) % mod;
						dp[i & 1][j - 1][k] = (dp[i & 1][j - 1][k] + (2 * dp[(i & 1) ^ 1][j][k] * k % mod * (j - 1) % mod) * (j > 1)) % mod;
					}
				}
		}
		io.writeln(dp[n & 1][1][0]);
	}
	return 0;
}
/*
dp[i][j][k] ǰ i �������� j ������һ���� k ���ڵ�
ת�Ƶ� i+1������ i+1 ������
0 �����ӣ�dp[i+1][j+1][k] = dp[i][j][k]
		 dp[i+1][j][k-1] = dp[i][j][k] * k
1 �����ӣ�dp[i+1][j+1][k] = dp[i][j][k] * 2
		 dp[i+1][j][k-1] = dp[i][j][k] * k * 2
2 �����ӣ�dp[i+1][j+1][k] = dp[i][j][k]
		 dp[i+1][j][k-1] = dp[i][j][k] * k
		 dp[i+1][j+1][k] = dp[i][j][k] * 2
		 dp[i+1][j][k-1] = dp[i][j][k] * k * 2
		 dp[i+1][j][k+1] = j * dp[i][j][k] * 2
		 dp[i+1][j-1][k] = (j-1) * dp[i][j][k] * 2
*/