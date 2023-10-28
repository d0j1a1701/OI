#include <algorithm>
#include <iostream>
#include <cstring>
#include <list>
using namespace std;
/* d0j1a_1701 FastIO full ver. 4.2 */
#define FIO //缓存模式 请勿在交互题开启
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
	template < typename Tp, typename enable_if < is_integral<Tp>::value || is_same<Tp, __int128_t>::value >::type * = nullptr >
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
const int MAXN = 3e5 + 5;
list<int> edges[MAXN];
int n, q;
int sm[MAXN << 2], ts[MAXN << 2], cov[MAXN << 2], tag[MAXN << 2];
inline void adj1(int x, int l, int r, int d) {
	sm[x] = (r - l + 1) * d;
	cov[x] = d;
}
inline void adj2(int x, int l, int r, int d) {
	ts[x] = tag[x] = d;
}
inline void pushdown(int x, int l, int r) {
	int mid = (l + r) >> 1;
	if(cov[x] != -1) {
		adj1(x << 1, l, mid, cov[x]);
		adj1(x << 1 | 1, mid + 1, r, cov[x]);
		cov[x] = -1;
	}
	if(tag[x] != -1) {
		adj2(x << 1, l, mid, tag[x]);
		adj2(x << 1 | 1, mid + 1, r, tag[x]);
		tag[x] = -1;
	}
}
inline void modify(int x, int l, int r, int L, int R, int d) {
	if(L > R) return;
	if(l == L && r == R) {
		adj1(x, l, r, d ? 0 : 1);
		if(d) adj2(x, l, r, d);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(x, l, r);
	if(R <= mid) modify(x << 1, l, mid, L, R, d);
	else if(L > mid) modify(x << 1 | 1, mid + 1, r, L, R, d);
	else modify(x << 1, l, mid, L, mid, d), modify(x << 1 | 1, mid + 1, r, mid + 1, R, d);
	sm[x] = sm[x << 1] + sm[x << 1 | 1];
}
inline void modify2(int x, int l, int r, int L, int R, int d) {
	if(L > R) return;
	if(l == L && r == R) {
		adj2(x, l, r, d);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(x, l, r);
	if(R <= mid) modify2(x << 1, l, mid, L, R, d);
	else if(L > mid) modify2(x << 1 | 1, mid + 1, r, L, R, d);
	else modify2(x << 1, l, mid, L, mid, d), modify2(x << 1 | 1, mid + 1, r, mid + 1, R, d);
	sm[x] = sm[x << 1] + sm[x << 1 | 1];
}
inline int query(int x, int l, int r, int L, int R) {
	if(L > R) return 0;
	if(l == L && r == R) return sm[x];
	int mid = (l + r) >> 1;
	pushdown(x, l, r);
	if(R <= mid) return query(x << 1, l, mid, L, R);
	if(L > mid) return query(x << 1 | 1, mid + 1, r, L, R);
	return query(x << 1, l, mid, L, mid) + query(x << 1 | 1, mid + 1, r, mid + 1, R);
}
inline int queryt(int x, int l, int r, int p) {
	if(l == r) return ts[x];
	int mid = (l + r) >> 1;
	pushdown(x, l, r);
	if(p <= mid) return queryt(x << 1, l, mid, p);
	else return queryt(x << 1 | 1, mid + 1, r, p);
}
inline void build(int x, int l, int r) {
	sm[x] = r - l + 1;
	tag[x] = cov[x] = -1;
	if(l == r)  return;
	int mid = (l + r) >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
}
int dfn[MAXN], rt[MAXN], son[MAXN], dep[MAXN], fa[MAXN], sz[MAXN], curT;
inline void dfs1(int u) {
	dep[u] = dep[fa[u]] + 1;
	sz[u] = 1;
	for(int v : edges[u]) {
		if(v == fa[u]) continue;
		fa[v] = u;
		dfs1(v);
		sz[u] += sz[v];
		son[u] = sz[son[u]] > sz[v] ? son[u] : v;
	}
}
inline void dfs2(int u, int curRt = 1) {
	dfn[u] = ++curT;
	rt[u] = curRt;
	if(son[u]) dfs2(son[u], curRt);
	for(int v : edges[u]) {
		if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v);
	}
}
int tim[MAXN];
inline void modify(int x, int y) {
	if(son[x]) modify(1, 1, n, dfn[son[x]], dfn[son[x]], 0);
	if(son[y]) modify(1, 1, n, dfn[son[y]], dfn[son[y]], 0);
	while(rt[x] != rt[y]) {
		if(dep[rt[x]] < dep[rt[y]]) swap(x, y);
		if(son[rt[x]]) modify(1, 1, n, dfn[son[rt[x]]], dfn[x], curT);
		modify2(1, 1, n, dfn[rt[x]], dfn[rt[x]], curT);
		tim[rt[x]] = curT;
		x = fa[rt[x]];
		if(son[x]) modify(1, 1, n, dfn[son[x]], dfn[son[x]], 0);
	}
	if(dep[x] > dep[y]) swap(x, y);
	modify(1, 1, n, dfn[x], dfn[y], curT);
	modify(1, 1, n, dfn[x], dfn[x], 0);
}
inline int query(int x, int y) {
	int res = 0;
	while(rt[x] != rt[y]) {
		if(dep[rt[x]] < dep[rt[y]]) swap(x, y);
		if(son[rt[x]]) res += query(1, 1, n, dfn[son[rt[x]]], dfn[x]);
		if(tim[rt[x]] < max(queryt(1, 1, n, dfn[fa[rt[x]]]), queryt(1, 1, n, dfn[rt[x]]))) res++;
		x = fa[rt[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	if(son[x]) res += query(1, 1, n, dfn[son[x]], dfn[y]);
	return res;
}
int main() {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	io.read(n);
	for(int i = 1; i < n; i++) {
		int u, v;
		io.read(u, v);
		edges[u].emplace_back(v);
		edges[v].emplace_back(u);
	}
	io.read(q);
	dfs1(1);
	dfs2(1);
	build(1, 1, n);
	fill(tim + 1, tim + 1 + n, -1);
	curT = 1;
	for(int op, x, y; curT <= q; curT++) {
		io.read(op, x, y);
		if(op == 1) modify(x, y);
		else io.writeln(query(x, y));
	}
	//system("pause");
	return 0;
}