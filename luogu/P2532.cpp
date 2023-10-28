#include <iostream>
#include <vector>
struct BigInt {
	int sign;
	std::vector<int>v;
	BigInt(): sign(1) {} BigInt(const std::string &s) {
		*this = s;
	} BigInt(int v) {
		char buf[21];
		sprintf(buf, "%d", v);
		*this = buf;
	} void zip(int unzip) {
		if(unzip == 0) {
			for(int i = 0; i < (int)v.size(); i++)v[i] = get_pos(i * 4) + get_pos(i * 4 + 1) * 10 + get_pos(i * 4 + 2) * 100 + get_pos(i * 4 + 3) * 1000;
		} else for(int i = (v.resize(v.size() * 4), (int)v.size() - 1), a; i >= 0; i--)a = (i % 4 >= 2) ? v[i / 4] / 100 : v[i / 4] % 100, v[i] = (i & 1) ? a / 10 : a % 10;
		setsign(1, 1);
	} int get_pos(unsigned pos)const {
		return pos >= v.size() ? 0 : v[pos];
	} BigInt &setsign(int newsign, int rev) {
		for(int i = (int)v.size() - 1; i > 0 && v[i] == 0; i--)v.erase(v.begin() + i);
		sign = (v.size() == 0 || (v.size() == 1 && v[0] == 0)) ? 1 : (rev ? newsign *sign : newsign);
		return*this;
	} std::string to_str()const {
		BigInt b = *this;
		std::string s;
		for(int i = (b.zip(1), 0); i < (int)b.v.size(); ++i)s += char(*(b.v.rbegin() + i) + '0');
		return(sign < 0 ? "-" : "") + (s.empty() ? std::string("0") : s);
	} bool absless(const BigInt &b)const {
		if(v.size() != b.v.size())return v.size() < b.v.size();
		for(int i = (int)v.size() - 1; i >= 0; i--)if(v[i] != b.v[i])return v[i] < b.v[i];
		return false;
	} BigInt operator-()const {
		BigInt c = *this;
		c.sign = (v.size() > 1 || v[0]) ? -c.sign : 1;
		return c;
	} BigInt &operator=(const std::string &s) {
		if(s[0] == '-')*this = s.substr(1);
		else {
			for(int i = (v.clear(), 0); i < (int)s.size(); ++i)v.push_back(*(s.rbegin() + i) - '0');
			zip(0);
		}
		return setsign(s[0] == '-' ? -1 : 1, sign = 1);
	} bool operator<(const BigInt &b)const {
		return sign != b.sign ? sign < b.sign : (sign == 1 ? absless(b) : b.absless(*this));
	} bool operator==(const BigInt &b)const {
		return v == b.v && sign == b.sign;
	} BigInt &operator+=(const BigInt &b) {
		if(sign != b.sign)return*this = (*this) - -b;
		v.resize(std::max(v.size(), b.v.size()) + 1);
		for(int i = 0, carry = 0; i < (int)b.v.size() || carry; i++) {
			carry += v[i] + b.get_pos(i);
			v[i] = carry % 10000, carry /= 10000;
		}
		return setsign(sign, 0);
	} BigInt operator+(const BigInt &b)const {
		BigInt c = *this;
		return c += b;
	} void add_mul(const BigInt &b, int mul) {
		v.resize(std::max(v.size(), b.v.size()) + 2);
		for(int i = 0, carry = 0; i < (int)b.v.size() || carry; i++) {
			carry += v[i] + b.get_pos(i) * mul;
			v[i] = carry % 10000, carry /= 10000;
		}
	} BigInt operator-(const BigInt &b)const {
		if(sign != b.sign)return(*this) + -b;
		if(absless(b))return -(b - *this);
		BigInt c;
		for(int i = 0, borrow = 0; i < (int)v.size(); i++) {
			borrow += v[i] - b.get_pos(i);
			c.v.push_back(borrow);
			c.v.back() -= 10000 * (borrow >>= 31);
		}
		return c.setsign(sign, 0);
	} BigInt operator*(const BigInt &b)const {
		if(b < *this)return b **this;
		BigInt c, d = b;
		for(int i = 0; i < (int)v.size(); i++, d.v.insert(d.v.begin(), 0))c.add_mul(d, v[i]);
		return c.setsign(sign * b.sign, 0);
	} BigInt operator/(const BigInt &b)const {
		BigInt c, d;
		d.v.resize(v.size());
		double db = 1.0 / (b.v.back() + (b.get_pos((unsigned)b.v.size() - 2) / 1e4) + (b.get_pos((unsigned)b.v.size() - 3) + 1) / 1e8);
		for(int i = (int)v.size() - 1; i >= 0; i--) {
			c.v.insert(c.v.begin(), v[i]);
			int m = (int)((c.get_pos((int)b.v.size()) * 10000 + c.get_pos((int)b.v.size() - 1)) * db);
			c = c - b * m, d.v[i] += m;
			while(!(c < b))c = c - b, d.v[i] += 1;
		}
		return d.setsign(sign * b.sign, 0);
	} BigInt operator%(const BigInt &b)const {
		return*this - *this / b * b;
	} bool operator>(const BigInt &b)const {
		return b < *this;
	} bool operator<=(const BigInt &b)const {
		return!(b < *this);
	} bool operator>=(const BigInt &b)const {
		return!(*this < b);
	} bool operator!=(const BigInt &b)const {
		return!(*this == b);
	}
};
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
BigInt f[510];
int n;
int main() {
	io.read(n);
	f[0] = f[1] = 1;
	for(int i = 2; i <= n; i++)
		f[i] = f[i - 1] * (4 * i - 2) / (i + 1);
	io.writeln(f[n].to_str());
	return 0;
}