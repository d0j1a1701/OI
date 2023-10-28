#include <concepts>
#include <iostream>
#include <stack>
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
	int read(Tp &x, Ts &...sum) {
		return read(x) && read(sum...);
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
	inline IO &write(Tp x, Ts... sum) {
		write(x);
		write(sep);
		write(sum...);
		return *this;
	}
	template<typename... Ts>
	inline IO &writeln(Ts... sum) {
		write(sum...);
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
namespace cmt {
const int N = 300010 * 30 + 10;
unsigned int sum[N], tag[N];
int idx, lc[N], rc[N];
void pushup(int id, int l, int r) {
	sum[id] = sum[lc[id]] + sum[rc[id]] + unsigned(r - l + 1) * tag[id];
}
void adjust(int pre, int &id, int l, int r, int x, int y, unsigned int val) {
	id = ++idx;
	lc[id] = lc[pre];
	rc[id] = rc[pre], sum[id] = sum[pre], tag[id] = tag[pre];
	if(x <= l && r <= y) {
		tag[id] += val;
		sum[id] += unsigned(r - l + 1) * val;
		return ;
	}
	int mid = (l + r) / 2;
	if(x <= mid) adjust(lc[pre], lc[id], l, mid, x, y, val);
	if(mid + 1 <= y) adjust(rc[pre], rc[id], mid + 1, r, x, y, val);
	pushup(id, l, r);
}
unsigned int query(int id, int l, int r, int x, int y, unsigned int lz = 0) {
	if(x <= l && r <= y) return lz * (r - l + 1) + sum[id];
	int mid = (l + r) / 2;
	unsigned int res = 0;
	if(x <= mid) res += query(lc[id], l, mid, x, y, lz + tag[id]);
	if(mid + 1 <= y) res += query(rc[id], mid + 1, r, x, y, lz + tag[id]);
	return res;
}
}
int n, m, a[300010], b[300010], l[300010], r[300010];
int ver[300010];
stack<int> stk;
inline unsigned int op1(int x, int y) {
	return (cmt::query(ver[y], 1, n, x, y) - cmt::query(ver[x - 1], 1, n, x, y)) * 114514;
}
inline unsigned int op2(int x, int y) {
	unsigned int sum = 0;
	for(int i = x; i <= y; i++)
		for(int j = i; j <= y; j++)
			sum += cmt::query(ver[j], 1, n, i, j) - cmt::query(ver[i - 1], 1, n, i, j);
	return sum * 114514;
}
int main() {
	freopen("together.in", "r", stdin);
	freopen("together.out", "w", stdout);
	io.read(n, m);
	for(int i = 1; i <= n; i++)	io.read(a[i]);
	for(int i = 1; i <= n; i++)	io.read(b[i]);
	for(int i = 1; i <= n; i++) {
		while(stk.size() && a[stk.top()] <= a[i])	stk.pop();
		l[i] = stk.size() ? stk.top() : 0;
		stk.push(i);
	}
	while(stk.size())	stk.pop();
	for(int i = n; i >= 1; i--) {
		while(stk.size() && a[stk.top()] <= a[i])	stk.pop();
		r[i] = stk.size() ? stk.top() : n + 1;
		stk.push(i);
	}
	// for(int i = 1; i <= n; i++)	io.writeWith(l[i]);
	// io.writeln();
	// for(int i = 1; i <= n; i++)	io.writeWith(r[i]);
	// io.writeln();
	for(int i = 1; i <= n; i++)
		cmt::adjust(ver[i - 1], ver[i], 1, n, l[i] + 1, r[i] - 1, b[i]);
	for(int i = 1, op, x, y; i <= m; i++) {
		io.read(op, x, y);
		if(op == 1) io.writeln(op1(x, y));
		else io.writeln(op2(x, y));
	}
	//system("pause");
	return 0;
}
/*
1 5 2 4 3
3 5 1 1 5

0 0 2 2 4
2 6 4 6 6

1 1 3
1 5 5
3 3 1
3 5 1
5 5 5

   1 2 3 4  5
0: 0 0 0 0  0
1: 3 0 0 0  0
2: 8 5 5 5  5
3: 8 5 6 5  5
4: 8 5 7 6  6
5: 8 5 7 6 11
*/