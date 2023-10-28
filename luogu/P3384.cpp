#include <iostream>
#include <vector>
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
		while(!isdigit(ch) && ch != EOF)	f = (ch == '-' ? -1 : 1), ch = getchar();
		while(isdigit(ch))	s = s * 10 + (ch ^ 48), ch = getchar();
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
		c = EOF;
		while(isspace(ch) && ch != EOF) ch = getchar();
		if(ch != EOF) c = ch;
		return c != EOF;
	}
	inline int read(char *c) {
		char ch = getchar(), *s = c;
		while(isspace(ch) && ch != EOF) ch = getchar();
		while(!isspace(ch) && ch != EOF) *(c++) = ch, ch = getchar();
		*c = '\0';
		return s != c;
	}
	inline int read(string &s) {
		s.clear();
		char ch = getchar();
		while(isspace(ch) && ch != EOF) ch = getchar();
		while(!isspace(ch) && ch != EOF) s += ch, ch = getchar();
		return s.size() > 0;
	}
	inline int getline(char *c, const char &ed = '\n') {
		char ch = getchar(), *s = c;
		while(ch != ed && ch != EOF)	*(c++) = ch, ch = getchar();
		*c = '\0';
		return s != c;
	}
	inline int getline(string &s, const char &ed = '\n') {
		s.clear();
		char ch = getchar();
		while(ch != ed && ch != EOF)	s += ch, ch = getchar();
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
		for(char ch : str) putchar(ch);
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
const int maxn = 100000;
int n, m, s, fa[maxn + 10], arr[maxn + 10];
vector<int> edges[maxn + 10];
long long p;
namespace hpd {
int sz[maxn + 10], dep[maxn + 10], cld[maxn + 10];
int tot, idx[maxn + 10], top[maxn + 10], dfn[maxn + 10];
int dfs1(int u) {
	dep[u] = dep[fa[u]] + 1, sz[u] = 1;
	for(int v : edges[u])
		if(v != fa[u]) {
			fa[v] = u;
			int vsz = dfs1(v);
			sz[u] += vsz;
			if(vsz > sz[cld[u]])	cld[u] = v;
		}
	return sz[u];
}
void dfs2(int u) {
	if(!u)	return;
	idx[u] = ++tot, dfn[tot] = u;
	top[cld[u]] = top[u], dfs2(cld[u]);
	for(int v : edges[u])
		if(v != fa[u] && v != cld[u])
			top[v] = v, dfs2(v);
}
inline void build(int s) {
	dfs1(s), top[s] = s, dfs2(s);
}
inline int lca(int u, int v) {
	while(top[u] != top[v])
		if(dep[top[u]] > dep[top[v]])	u = fa[top[u]];
		else v = fa[top[v]];
	return dep[u] <= dep[v] ? u : v;
}
}
namespace smt {
long long tree[4 * maxn + 10], add[4 * maxn + 10];
inline void pushup(int id) {
	tree[id] = (tree[id * 2] + tree[id * 2 + 1]) % p;
}
inline void pushdown(int id, int l, int r) {
	if(add[id]) {
		int mid = (l + r) / 2;
		add[id * 2] = (add[id * 2] + add[id]) % p;
		add[id * 2 + 1] = (add[id * 2 + 1] + add[id]) % p;
		tree[id * 2] = (tree[id * 2] + add[id] * (mid - l + 1)) % p;
		tree[id * 2 + 1] = (tree[id * 2 + 1] + add[id] * (r - mid)) % p;
		add[id] = 0;
	}
}
void build(int id, int l, int r) {
	if(l == r) return tree[id] = arr[hpd::dfn[l]] % p, void();
	int mid = (l + r) / 2;
	build(id * 2, l, mid), build(id * 2 + 1, mid + 1, r);
	pushup(id);
}
void adjust(int id, int l, int r, int x, int y, long long v) {
	if(x <= l && r <= y) {
		tree[id] = (tree[id] + v * (r - l + 1)) % p;
		add[id] += v;
		return;
	}
	pushdown(id, l, r);
	int mid = (l + r) / 2;
	if(x <= mid)	adjust(id * 2, l, mid, x, y, v);
	if(mid < y)		adjust(id * 2 + 1, mid + 1, r, x, y, v);
	pushup(id);
}
long long query(int id, int l, int r, int x, int y) {
	if(x <= l && r <= y)	return tree[id];
	pushdown(id, l, r);
	long long mid = (l + r) / 2, res = 0;
	if(x <= mid)	res = query(id * 2, l, mid, x, y);
	if(mid < y)		res = (res + query(id * 2 + 1, mid + 1, r, x, y)) % p;
	return res;
}
}
inline void adjust_path(int u, int v, long long x) {
	while(hpd::top[u] != hpd::top[v]) {
		if(hpd::dep[hpd::top[u]] < hpd::dep[hpd::top[v]])	swap(u, v);
		smt::adjust(1, 1, n, hpd::idx[hpd::top[u]], hpd::idx[u], x);
		u = fa[hpd::top[u]];
	}
	if(hpd::dep[u] > hpd::dep[v])	swap(u, v);
	smt::adjust(1, 1, n, hpd::idx[u], hpd::idx[v], x);
}
inline long long query_path(int u, int v) {
	long long res = 0;
	while(hpd::top[u] != hpd::top[v]) {
		if(hpd::dep[hpd::top[u]] < hpd::dep[hpd::top[v]])	swap(u, v);
		res = (res + smt::query(1, 1, n, hpd::idx[hpd::top[u]], hpd::idx[u])) % p;
		u = fa[hpd::top[u]];
	}
	if(hpd::dep[u] > hpd::dep[v])	swap(u, v);
	res = (res + smt::query(1, 1, n, hpd::idx[u], hpd::idx[v])) % p;
	return res;
}
inline void adjust_tree(int u, long long x) {
	smt::adjust(1, 1, n, hpd::idx[u], hpd::idx[u] + hpd::sz[u] - 1, x);
}
inline long long query_tree(int u) {
	return smt::query(1, 1, n, hpd::idx[u], hpd::idx[u] + hpd::sz[u] - 1);
}
int main() {
	io.read(n, m, s, p);
	for(int i = 1; i <= n; i++) io.read(arr[i]);
	for(int i = 1, u, v; i < n; i++) {
		io.read(u, v);
		edges[u].emplace_back(v);
		edges[v].emplace_back(u);
	}
	hpd::build(s), smt::build(1, 1, n);
	for(int i = 1, a, b, c, d; i <= m; i++) {
		io.read(a);
		if(a == 1)	io.read(b, c, d), adjust_path(b, c, d);
		else if(a == 2)	io.read(b, c), io.writeln(query_path(b, c));
		else if(a == 3)	io.read(b, c), adjust_tree(b, c);
		else io.read(b), io.writeln(query_tree(b));
	}
	//system("pause");
	return 0;
}