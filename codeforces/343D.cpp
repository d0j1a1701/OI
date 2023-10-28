#include <iostream>
#include <cstring>
#include <list>
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
const int N = 500010;
int n, m, cnt, top[N], fa[N], dfn[N], id[N], sz[N], dep[N], hs[N];
int col[4 * N], tag[4 * N];
list<int> edges[N];
void build(int u) {
	sz[u] = 1;
	for(int v : edges[u]) {
		if(dep[v])	continue;
		fa[v] = u;
		dep[v] = dep[u]  + 1;
		build(v);
		sz[u] += sz[v];
		if(sz[v] > sz[hs[u]])	hs[u] = v;
	}
}
void dfs(int u, int topfa) {
	dfn[u] = ++cnt;
	id[cnt] = u;
	top[u] = topfa;
	if(hs[u])	dfs(hs[u], topfa);
	for(int v : edges[u]) {
		if(fa[u] == v || v == hs[u])	continue;
		dfs(v, v);
	}
}
void pushdown(int id) {
	col[id << 1] = col[id << 1 | 1] = col[id];
	tag[id << 1] = tag[id << 1 | 1] = tag[id];
	tag[id] = -1;
}
void adjust(int id, int l, int r, int x, int y, int k) {
	if(x <= l && r <= y) {
		col[id] = k;
		tag[id] = k;
		return ;
	}
	int mid = (l + r) >> 1;
	if(tag[id] >= 0)	pushdown(id);
	if(x <= mid)	adjust(id << 1, l, mid, x, y, k);
	if(y > mid)		adjust(id << 1 | 1, mid + 1, r, x, y, k);
}
void adjust2(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]])	swap(x, y);
		adjust(1, 1, n, dfn[top[x]], dfn[x], 0);
		x = fa[top[x]];
	}
	if(dep[x] < dep[y])	swap(x, y);
	adjust(1, 1, n, dfn[y], dfn[x], 0);
}
int query(int id, int l, int r, int x) {
	if(l == r)	return col[id];
	int mid = (l + r) >> 1;
	if(tag[id] >= 0)	pushdown(id);
	if(x <= mid)	return query(id << 1, l, mid, x);
	else	return query(id << 1 | 1, mid + 1, r, x);
}
int main() {
	io.read(n);
	for(int i = 1, u, v; i < n; i ++) {
		io.read(u, v);
		edges[u].emplace_back(v);
		edges[v].emplace_back(u);
	}
	cnt = 0, dep[1] = 1;
	build(1);
	dfs(1, 1);
	memset(tag, -1, sizeof tag);
	io.read(m);
	for(int i = 1, op, x; i <= m; i ++) {
		io.read(op, x);
		if(op == 1)	adjust(1, 1, n, dfn[x], dfn[x] + sz[x] - 1, 1);
		else if(op == 2)	adjust2(1, x);
		else io.writeln(query(1, 1, n, dfn[x]));
	}
	return 0;
}
