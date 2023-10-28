#include <iostream>
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
		while(isdigit(ch))	s = s * 10 + (ch ^ 48), ch = getchar();
		if(ch == EOF)	return false;
		if(ch == '.') {
			Tp eps = 0.1;
			ch = getchar();
			while(isdigit(ch))	s = s + (ch ^ 48) * eps, ch = getchar(), eps /= 10;
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
const int inf = 0x3f3f3f3f;
struct Node {
	int a, b, lans, rans, ans;
	Node() {
		lans = rans = ans = -inf;
	}
} tree[2000010];
int n, m, A[500010], B[500010];
inline void pushup(const int &id) {
	tree[id].a = max(tree[id * 2].a, tree[id * 2 + 1].a), tree[id].b = min(tree[id * 2].b, tree[id * 2 + 1].b);
	tree[id].lans = max(tree[id * 2].lans, max(tree[id * 2 + 1].lans, tree[id * 2].a - tree[id * 2 + 1].b));
	tree[id].rans = max(tree[id * 2].rans, max(tree[id * 2 + 1].rans, tree[id * 2 + 1].a - tree[id * 2].b));
	tree[id].ans = max(max(tree[id * 2].ans, tree[id * 2 + 1].ans), max(tree[id * 2].lans + tree[id * 2 + 1].a, tree[id * 2 + 1].rans + tree[id * 2].a));
}
void build(int id, int l, int r) {
	if(l == r) {
		tree[id].a = A[l];
		tree[id].b = B[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(id << 1, l, mid), build(id << 1 | 1, mid + 1, r);
	pushup(id);
}
void adjust1(int id, int l, int r, int pos, int val) {
	if(l == r) {
		tree[id].a = val;
		return;
	}
	int mid = (l + r) >> 1;
	if(mid >= pos) adjust1(id << 1, l, mid, pos, val);
	else adjust1(id << 1 | 1, mid + 1, r, pos, val);
	pushup(id);
}
void adjust2(int id, int l, int r, int pos, int val) {
	if(l == r) {
		tree[id].b = val;
		return;
	}
	int mid = (l + r) >> 1;
	if(mid >= pos) adjust2(id << 1, l, mid, pos, val);
	else adjust2(id << 1 | 1, mid + 1, r, pos, val);
	pushup(id);
}
Node query(int id, int l, int r, int L, int R) {
	if(L <= l && r <= R) return tree[id];
	int mid = (l + r) >> 1;
	if(mid >= R) return query(id << 1, l, mid, L, R);
	if(mid < L) return query(id << 1 | 1, mid + 1, r, L, R);
	Node ret, x = query(id << 1, l, mid, L, R), y = query(id << 1 | 1, mid + 1, r, L, R);
	ret.a = max(x.a, y.a);
	ret.b = min(x.b, y.b);
	ret.ans = max(max(x.ans, y.ans), max(x.lans + y.a, y.rans + x.a));
	ret.lans = max(x.lans, max(y.lans, x.a - y.b));
	ret.rans = max(x.rans, max(y.rans, y.a - x.b));
	return ret;
}
int main() {
	io.read(n, m);
	for(int i = 1; i <= n; i++) io.read(A[i]);
	for(int i = 1; i <= n; i++) io.read(B[i]);
	build(1, 1, n);
	for(int i = 1, op, x, y; i <= m; i++) {
		io.read(op, x, y);
		if(op == 1) adjust1(1, 1, n, x, y);
		else if(op == 2) adjust2(1, 1, n, x, y);
		else io.writeln(query(1, 1, n, x, y).ans);
	}

	system("pause");
	return 0;
}