#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
int n, dp[210][1010];
char str[210];
int main() {
	while(~scanf("%s", str + 1)) {
		n = strlen(str + 1);
		int base = str[1] == '0' ? 0 : 1000;
		for(int j = 0; j <= 1000; j++)    dp[1][j] = (j - base) * (j - base);
		for(int i = 2; i <= n; i++) {
			base = str[i] == '0' ? 0 : 1000;
			for(int j = 0, Min = 1e9; j <= 1000; j++) {
				if(dp[i - 1][j] < Min)
					Min = dp[i - 1][j];
				dp[i][j] = Min + (j - base) * (j - base);
			}
		}
		printf("%.3lf\n", (*min_element(dp[n], dp[n] + 1000 + 1)) / 1000000.0);
	}
	//system("pause");
	return 0;
}