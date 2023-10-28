#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
/* d0j1a_1701 FastIO full ver. 4.2 */
//#define FIO //缓存模式 请勿在交互题开启
struct IO {
#ifdef FIO
	const static int BUFSIZE = 1 << 20;
	char buf[BUFSIZE], obuf[BUFSIZE], *p1, *p2, *pp;
	inline char getchar() {
		return(p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, BUFSIZE, stdin), p1 == p2) ? EOF : *p1++);
	} inline void putchar(char x) {
		((pp - obuf == BUFSIZE && (fwrite(obuf, 1, BUFSIZE, stdout), pp = obuf)), *pp = x, pp++);
	} inline IO &flush() {
		fwrite(obuf, 1, pp - obuf, stdout);
		fflush(stdout);
		return*this;
	} IO() {
		p1 = buf, p2 = buf, pp = obuf;
	}~IO() {
		flush();
	}
#else
	int(*getchar)() = &::getchar;
	int(*putchar)(int) = &::putchar;
	inline IO &flush() {
		fflush(stdout);
		return*this;
	};
#endif
	string sep = " ";
	int k = 2;
	template < typename Tp, typename std::enable_if < std::is_integral<Tp>::value || std::is_same<Tp, __int128_t>::value >::type * = nullptr > inline int read(Tp &s) {
		int f = 1;
		char ch = getchar();
		s = 0;
		while(!isdigit(ch) && ch != EOF)f = (ch == '-' ? -1 : 1), ch = getchar();
		while(isdigit(ch))s = s * 10 + (ch ^ 48), ch = getchar();
		s *= f;
		return ch != EOF;
	} template<typename Tp, typename enable_if<is_floating_point<Tp>::value>::type * = nullptr>inline int read(Tp &s) {
		int f = 1;
		char ch = getchar();
		s = 0;
		while(!isdigit(ch) && ch != EOF && ch != '.')f = (ch == '-' ? -1 : 1), ch = getchar();
		while(isdigit(ch))s = s * 10 + (ch ^ 48), ch = getchar();
		if(ch == EOF)return false;
		if(ch == '.') {
			Tp eps = 0.1;
			ch = getchar();
			while(isdigit(ch))s = s + (ch ^ 48) * eps, ch = getchar(), eps /= 10;
		}
		s *= f;
		return ch != EOF;
	} inline int read(char &c) {
		char ch = getchar();
		c = EOF;
		while(isspace(ch) && ch != EOF)ch = getchar();
		if(ch != EOF)c = ch;
		return c != EOF;
	} inline int read(char *c) {
		char ch = getchar(), *s = c;
		while(isspace(ch) && ch != EOF)ch = getchar();
		while(!isspace(ch) && ch != EOF)*(c++) = ch, ch = getchar();
		*c = '\0';
		return s != c;
	} inline int read(string &s) {
		s.clear();
		char ch = getchar();
		while(isspace(ch) && ch != EOF)ch = getchar();
		while(!isspace(ch) && ch != EOF)s += ch, ch = getchar();
		return s.size() > 0;
	} inline int getline(char *c, const char &ed = '\n') {
		char ch = getchar(), *s = c;
		while(ch != ed && ch != EOF)*(c++) = ch, ch = getchar();
		*c = '\0';
		return s != c;
	} inline int getline(string &s, const char &ed = '\n') {
		s.clear();
		char ch = getchar();
		while(ch != ed && ch != EOF)s += ch, ch = getchar();
		return s.size() > 0;
	} template<typename Tp = int>inline Tp read() {
		Tp x;
		read(x);
		return x;
	} template<typename Tp, typename...Ts>int read(Tp &x, Ts &...val) {
		return read(x) && read(val...);
	} template<typename Tp, typename enable_if<is_integral<Tp>::value>::type * = nullptr>IO & write(Tp x) {
		if(x < 0)putchar('-'), x = -x;
		static char sta[20];
		int top = 0;
		do sta[top++] = x % 10 + '0', x /= 10;
		while(x);
		while(top)putchar(sta[--top]);
		return*this;
	} inline IO &write(const string &str) {
		for(char ch : str)putchar(ch);
		return*this;
	} inline IO &write(const char *str) {
		while(*str != '\0')putchar(*(str++));
		return*this;
	} inline IO &write(char *str) {
		return write((const char *)str);
	} inline IO &write(const char &ch) {
		return putchar(ch), *this;
	} template<typename Tp, typename enable_if<is_floating_point<Tp>::value>::type * = nullptr>inline IO & write(Tp x) {
		if(x > 1e18 || x < -1e18) {
			write("[Floating point overflow]");
			throw;
		}
		if(x < 0)putchar('-'), x = -x;
		const static long long pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000, 10000000000000000, 100000000000000000, 100000000000000000, 100000000000000000};
		const auto &n = pow10[k];
		long long whole = (int)x;
		double tmp = (x - whole) * n;
		long long frac = tmp;
		double diff = tmp - frac;
		if(diff > 0.5) {
			++frac;
			if(frac >= n)frac = 0, ++whole;
		} else if(diff == 0.5 && ((frac == 0U) || (frac & 1U)))++frac;
		write(whole);
		if(k == 0U) {
			diff = x - (double)whole;
			if((!(diff < 0.5) || (diff > 0.5)) && (whole & 1))++whole;
		} else {
			putchar('.');
			static char sta[20];
			int count = k, top = 0;
			while(frac) {
				sta[top++] = frac % 10 + '0';
				frac /= 10, count--;
			}
			while(count--)putchar('0');
			while(top)putchar(sta[--top]);
		}
		return*this;
	} template<typename Tp, typename...Ts>inline IO &write(Tp x, Ts...val) {
		write(x);
		write(sep);
		write(val...);
		return*this;
	} template<typename...Ts>inline IO &writeln(Ts...val) {
		write(val...);
		putchar('\n');
		return*this;
	} inline IO &writeln(void) {
		putchar('\n');
		return*this;
	} template<typename Tp>inline IO &writeWith(Tp x, const string &s = " ") {
		write(x), write(s);
		return*this;
	} inline IO &setsep(const string &s) {
		return sep = s, *this;
	} inline IO &setprec(const int &K) {
		return k = K, *this;
	}
} io;
vector<pair<int, int> > edges[100010];
int n, m, res, vis[100010], X, Y, C;
bool findExtraEdge(int u, int fa = 0) {
	vis[u] = 1;
	for(auto edge : edges[u]) {
		int v = edge.first, c = edge.second;
		if(v == fa)	continue;
		else if(!vis[v]) {
			if(findExtraEdge(v, u))	return 1;
		} else if(vis[v] == 1) {
			X = u, Y = v, C = c;
			return 1;
		}
	}
	vis[u] = 2;
	return 0;
}
void dfs(int u, int fa = 0, int col = 0) {
	//io.writeln(u,fa,col);
	for(auto edge : edges[u]) {
		int v = edge.first, c = edge.second;
		if(u == X && v == Y)	continue;
		if(u == Y && v == X)	continue;
		//io.writeln(u,"->",v,c);
		if(v == fa)	continue;
		if(c != col)	res++;
		dfs(v, u, c);
	}
}
auto cmp = [](auto a, auto b) {
	return a.second < b.second;
};
pair<int, int> NUL;
auto &getEdge(int u, int v) {
	for(auto &edge : edges[u])
		if(edge.first == v)
			return edge;
	return NUL;
}
inline int colorCount(int u, int c) {
	int cnt = 0;
	for(auto &edge : edges[u])
		if(edge.second == c)
			cnt++;
	return cnt;
}
int main() {
	//freopen("color.in","r",stdin);
	//freopen("color.out","w",stdout);
	io.read(n, m);
	for(int i = 1, u, v, c; i <= n; i++) {
		io.read(u, v, c);
		edges[u].emplace_back(v, c);
		edges[v].emplace_back(u, c);
	}
	for(int i = 1; i <= n; i++)	sort(edges[i].begin(), edges[i].end(), cmp);
	findExtraEdge(1), memset(vis, 0, sizeof(vis));
	//io.writeln("qwq:",X,Y,C);
	dfs(1);
	//io.writeln("qwq",res);
	int cnt = (colorCount(X, C) > 1) + (colorCount(Y, C) > 1);
	if(cnt == 0)		res++;
	else if(cnt == 2)	res--;
	edges[X].emplace_back(Y, C);
	edges[Y].emplace_back(X, C);
	//io.writeln(res);
	for(int i = 1, u, v, c; i <= m; i++) {
		io.read(u, v, c);
		auto &e1 = getEdge(u, v);
		if(e1.second == c) {
			io.writeln(res);
			continue;
		}
		int cnt1 = 0, cnt2 = 0;
		if(colorCount(u, c) > 1)	cnt1++;
		if(colorCount(v, c) > 1)	cnt1++;
		if(colorCount(u, e1.second) > 1)	cnt2++;
		if(colorCount(v, e1.second) > 1)	cnt2++;
		io.writeln(cnt1, cnt2);
		if(cnt1 == 1 && cnt2 == 0)	res--;
		else if(cnt1 == 0 && cnt2 == 1)	res++;
		else if(cnt1 == 0 && cnt2 == 2)	res += 2;
		else if(cnt1 == 2 && cnt2 == 0)	res -= 2;
		e1.second = getEdge(v, u).second = c;
		io.writeln(res);
	}
	return 0;
}
