#include <iostream>
#include <cstdio>
using namespace std;
int t, n;
inline int ask(int l, int r) {
	printf("? %d %d\n", l, r);
	fflush(stdout);
	int x;
	scanf("%d", &x);
	return x;
}
inline void determine(int x) {
	printf("! %d\n", x);
	fflush(stdout);
}
int solve(int l, int r) {
	if(l == r)    return l;
	if(l + 1 == r)  return ask(l, r) == 1 ? l : r;
	int mid = (l + r) / 2;
	int a = solve(l, mid), b = solve(mid + 1, r);
	return (ask(l, b) == ask(l, b - 1) ? b : a);
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		determine(solve(1, n));
	}
	system("pause");
	return 0;
}
/*
  3 1 4 2
1   *   *
2
3       *
4
*/