#include <iostream>
#include <set>
using namespace std;
/* d0j1a_1701 FastIO full ver. 3.6 */
//#define FIO //开启加速模式 将不能使用键盘读入
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
const long long mod1 = 1000000007, mod2 = 1000000009;
long long hsh1[200010], mul1[200010], hsh2[200010], mul2[200010];
int t, n, m, pfx1[200010];
char str[200010];
inline long long getHash(long long *hsh, long long *mul, long long mod, int l, int r) {
	if(l > r) return 0;
	return ((hsh[r] - hsh[l - 1] * mul[r - l + 1] % mod) + mod) % mod;
}
int main() {
	mul1[0] = mul2[0] = 1;
	for(int i = 1; i <= 200000; i++) mul1[i] = mul1[i - 1] * 13331 % mod1;
	for(int i = 1; i <= 200000; i++) mul2[i] = mul2[i - 1] * 13331 % mod2;
	io.read(t);
	while(t--) {
		io.read(n, m);
		io.read(str + 1);
		set<long long> s;
		for(int i = 1; i <= n; i++)   str[i] -= '0';
		for(int i = 1; i <= n; i++)   hsh1[i] = (hsh1[i - 1] * 13331 % mod1 + str[i]) % mod1;
		for(int i = 1; i <= n; i++)   hsh2[i] = (hsh2[i - 1] * 13331 % mod2 + str[i]) % mod2;
		for(int i = 1; i <= n; i++)   pfx1[i] = pfx1[i - 1] + (str[i] == 1);
		// while(1) {
		// 	int l, r;
		// 	io.read(l, r);
		// 	io.writeln(getHash(hsh1, mul1, mod1, l, r));
		// }
		for(int i = 1, l, r; i <= m; i++) {
			io.read(l, r);
			long long before_hash1, after_hash1, middle_hash1;
			long long before_hash2, after_hash2, middle_hash2;
			before_hash1 = getHash(hsh1, mul1, mod1, 1, l - 1);
			before_hash2 = getHash(hsh2, mul2, mod2, 1, l - 1);
			after_hash1 = getHash(hsh1, mul1, mod1, r + 1, n);
			after_hash2 = getHash(hsh2, mul2, mod2, r + 1, n);
			long long cnt1 = pfx1[r] - pfx1[l - 1];
			middle_hash1 = (mul1[cnt1] - 1) * 356114031 % mod1;
			middle_hash2 = (mul2[cnt1] - 1) * 339159793 % mod2;
			//middle_hash1 = getHash(hsh1, mul1, mod1, l, r);
			//middle_hash2 = getHash(hsh2, mul2, mod2, l, r);
			long long h1 = ((before_hash1 * mul1[r - l + 1] % mod1 + middle_hash1) % mod1 * mul1[n - r] % mod1 + after_hash1) % mod1;
			long long h2 = ((before_hash2 * mul2[r - l + 1] % mod2 + middle_hash2) % mod2 * mul2[n - r] % mod2 + after_hash2) % mod2;
			s.insert((h1 << 31) + h2);
		}
		io.writeln(s.size());
	}
	//system("pause");
	return 0;
}