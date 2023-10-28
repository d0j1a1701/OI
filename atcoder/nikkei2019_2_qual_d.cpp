#include <algorithm>
#include <iostream>
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
struct Edge {
	int l, r, c;
} arr[100010];
long long tree[4 * 100000 + 10], tag[4 * 100000 + 10];
inline void pushup(int id) {
	tree[id] = min(tree[id << 1], tree[id << 1 | 1]);
}
inline void pushdown(int id) {
	if(tag[id] != 1e18) {
		tree[id << 1] = min(tree[id << 1], tag[id]);
		tree[id << 1 | 1] = min(tree[id << 1 | 1], tag[id]);
		tag[id << 1] = min(tag[id << 1], tag[id]);
		tag[id << 1 | 1] = min(tag[id << 1 | 1], tag[id]);
		tag[id] = 1e18;
	}
}
void build(int id, int l, int r) {
	if(l == r)    return tree[id] = 1e18, void();
	int mid = (l + r) >> 1;
	build(id << 1, l, mid), build(id << 1 | 1, mid + 1, r);
	tree[id] = tag[id] = 1e18;
}
void adjust(int id, int l, int r, int x, int y, long long val) {
	if(x <= l && r <= y) {
		tree[id] = min(tree[id], val);
		tag[id] = min(tag[id], val);
		return;
	}
	pushdown(id);
	int mid = (l + r) >> 1;
	if(x <= mid)	adjust(id << 1, l, mid, x, y, val);
	if(mid < y)     adjust(id << 1 | 1, mid + 1, r, x, y, val);
	pushup(id);
}
long long query(int id, int l, int r, int x, int y) {
	if(x <= l && r <= y)	return tree[id];
	pushdown(id);
	long long mid = (l + r) >> 1, res = 1e18;
	if(x <= mid)	res = query(id << 1, l, mid, x, y);
	if(mid < y)     res = min(res, query(id << 1 | 1, mid + 1, r, x, y));
	return res;
}
int n, m;
int main() {
	io.read(n, m);
	build(1, 1, n);
	for(int i = 1; i <= m; i++)   io.read(arr[i].l, arr[i].r, arr[i].c);
	sort(arr + 1, arr + 1 + m, [](auto a, auto b) {
		return a.l == b.l ? (a.r == b.r ? a.c < b.c : a.r < b.r) : a.l < b.l;
	});
	adjust(1, 1, n, 1, 1, 0);
	for(int i = 1; i <= m; i++) {
		auto [l, r, c] = arr[i];
		auto mn = query(1, 1, n, l, r);
		adjust(1, 1, n, l, r, mn + c);
	}
	long long res = query(1, 1, n, n, n);
	io.writeln(res == 1e18 ? -1 : res);
	//system("pause");
	return 0;
}
/*
1 2 3 4

2 2 2
6 6 6 6
  3 3 3
*/