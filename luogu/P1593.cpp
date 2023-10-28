#include <iostream>
#include <iterator>
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
const int mod = 9901;
int qpow(int a, int b, int m = mod) {
	int res = 1;
	for(; b; a = a * a % m, b >>= 1)
		if(b & 1) res = res * a % m;
	return res;
}
int a, b, arr[50000010][2], cnt, res = 1;
int sum(int x, int y) {
	y = y * b;
	if(x % mod == 1) return (y + 1) % mod;
	return (qpow(x % mod, y + 1) - 1) % mod * qpow((x - 1) % mod, mod - 2) % mod;
}
int main() {
	io.read(a, b);
	if(!a) goto end;
	for(int i = 2; i * i <= a; i++) {
		if(a % i == 0) {
			cnt++, arr[cnt][0] = i, arr[cnt][1] = 1;
			a = a / i;
			while(a % i == 0) {
				arr[cnt][1]++;
				a = a / i;
			}
		}
	}
	if(a > 1) {
		cnt++;
		arr[cnt][0] = a, arr[cnt][1] = 1;
	}
	for(int i = 1; i <= cnt; i++)
		res = res * sum(arr[i][0], arr[i][1]) % mod;
end:
	io.writeln((res % mod + mod) % mod);
	//system("pause");
	return 0;
}