#include <bits/stdc++.h>

#define int long long

using namespace std;
const int M = 10, MOD = 998244353;

int T;
int dp[M][M][M][M]; // 第一维存长度，后面存最后四位数字的状态，因为第五位可以循环递推

int n, m;

void solve()
{
    int res = 0;
    cin >> n >> m;
    for (int i = 1; i <= m && i <= 9; i += 2) // 奇偶交替
        for (int j = 0; j <= m - i && j <= 9; j += 2)
            for (int k = 1; k <= m - i - j && k <= 9; k += 2)
                for (int l = 0; l <= m - i - j - k && l <= 9; l += 2)
                    dp[i][j][k][l] = 1; // 只有这几种状态是合法的，其余状态均不合法，不计入总方案

    for (int len = 5; len <= n; len++)
        for (int i = (len + 1) % 2; i <= m && i <= 9; i += 2)
            for (int j = len % 2; j <= m - i && j <= 9; j += 2)
                for (int k = (len + 1) % 2; k <= m - i - j && k <= 9; k += 2)
                    for (int l = len % 2; l <= m - i - j - k && l <= 9; l += 2)
                    {
                        for (int o = len % 2; o <= m - i - j - k - l && o <= 9; o += 2)
                            dp[i][j][k][o] = (dp[i][j][k][o] + dp[l][i][j][k]) % MOD;
                        dp[l][i][j][k] = 0;
                    }

    for (int i = (n + 1) % 2; i <= m && i <= 9; i += 2)
        for (int j = n % 2; j <= m - i && j <= 9; j += 2)
            for (int k = (n + 1) % 2; k <= m - i - j && k <= 9; k += 2)
                for (int l = n % 2; l <= m - i - j - k && l <= 9; l += 2)
                    res = (res + dp[i][j][k][l]) % MOD;

    cout << res << '\n';
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // cin >> T;
    T = 1;
    while (T--)
    {
        solve();
    }

    return 0;
}