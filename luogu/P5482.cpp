#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <set>
using namespace std;
/* d0j1a_1701 FastIO full ver. 3.5 */
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
		fwrite("Warning: Macro 'FIO' has been defined, keyboard input will be ignored.\n", 1, 71, stderr);
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int len, lc[100010], rc[100010], sz[100010], w[100010], val[100010];
struct Treap {
	int root;
	inline int newNode(int x) {
		return len++, sz[len] = 1, w[len] = rng(), val[len] = x, len;
	}
	inline void pushup(int id) {
		sz[id] = sz[lc[id]] + sz[rc[id]] + 1;
	}
	void split(int id, int k, int &x, int &y) {
		if(!id) return x = y = 0, void();
		if(val[id] <= k) x = id, split(rc[id], k, rc[id], y);
		else y = id, split(lc[id], k, x, lc[id]);
		pushup(id);
	}
	int merge(int x, int y) {
		if(!x || !y)  return x + y;
		if(w[x] >= w[y])  return rc[x] = merge(rc[x], y), pushup(x), x;
		return lc[y] = merge(x, lc[y]), pushup(y), y;
	}
	inline void insert(int x) {
		int a, b;
		split(root, x, a, b);
		root = merge(merge(a, newNode(x)), b);
	}
	inline void erase(int x) {
		int a, b, c;
		split(root, x, a, c), split(a, x - 1, a, b);
		root = merge(merge(a, merge(lc[b], rc[b])), c);
	}
	inline int count_less(int x) { // < x 的有多少个
		int a, b, res;
		split(root, x - 1, a, b);
		res = sz[a];
		root = merge(a, b);
		return res;
	}
	inline int count_greater(int x) { // > x 的有多少个
		int a, b, res;
		split(root, x, a, b);
		res = sz[b];
		root = merge(a, b);
		return res;
	}
	void ldr(int id) {
		if(!id) return;
		ldr(lc[id]);
		io.writeWith(val[id], " ");
		ldr(rc[id]);
	}
} t1/*a>0*/, t2/*a<0*/;
set<int> always_true;
int n, cnt, A[100010], typ[100010];
int main() {
	io.read(n);
	string op;
	for(int i = 1, a, b, c; i <= n; i++) {
		io.read(op, a);
		if(op == "Add") {
			io.read(b, c), ++cnt;
			if(a == 0 && b > c) always_true.emplace(cnt), typ[cnt] = 1;
			else if(a > 0) t1.insert(A[cnt] = floor((1.0 * c - b) / a)), typ[cnt] = 2;
			else if(a < 0) t2.insert(A[cnt] = ceil((1.0 * c - b) / a)), typ[cnt] = 3;
		} else if(op == "Del") {
			if(typ[a] == 1)   always_true.erase(a);
			else if(typ[a] == 2)  t1.erase(A[a]);
			else if(typ[a] == 3)  t2.erase(A[a]);
		} else
			io.writeln(always_true.size() + t1.count_less(a) + t2.count_greater(a));
		// io.write("t1: "), t1.ldr(t1.root), io.writeln();
		// io.write("t2: "), t2.ldr(t2.root), io.writeln();
	}
	system("pause");
	return 0;
}