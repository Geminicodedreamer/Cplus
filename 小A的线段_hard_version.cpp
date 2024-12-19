#include <bits/stdc++.h>

using namespace std;
const int N = 210, MOD = 998244353;
typedef pair<int, int> PII;

int T;
int n, m;
map<PII, int> dp;

void solve()
{
    cin >> n >> m;
    vector<PII> a(m + 1);
    for (int i = 1; i <= m; i++)
        cin >> a[i].first >> a[i].second;

    sort(a.begin(), a.end(), [&](PII a, PII b)
         {
        if(a.first != b.first) return a.first < b.first;
        return a.second > b.second; });

    dp[{0, 0}] = 1;
    for (int i = 1; i <= m; i++)
    {
        auto d = dp;
        auto [L, R] = a[i];
        for (auto [it, v] : dp)
        {
            auto [l, r] = it;
            if (L <= l)
            {
                if (R <= l)
                { // 这条线段选或不选
                    d[{l, r}] = (d[{l, r}] + dp[{l, r}]) % MOD;
                }
                else if (R <= r)
                { // L <= l < R <= r
                    d[{R, r}] = (d[{R, r}] + dp[{l, r}]) % MOD;
                }
                else
                { // L <= l <= r < R
                    d[{r, R}] = (d[{r, R}] + dp[{l, r}]) % MOD;
                }
            }
            else if (L == l + 1)
            { // l < L <= r
                if (R <= r)
                { // L <= l < R <= r
                    d[{R, r}] = (d[{R, r}] + dp[{l, r}]) % MOD;
                }
                else
                { // l < L <= r < R
                    d[{r, R}] = (d[{r, R}] + dp[{l, r}]) % MOD;
                }
            }
            else if (L == r + 1)
            {
                d[{l, R}] = (d[{l, R}] + dp[{l, r}]) % MOD;
            }
        }
        swap(dp, d);
    }

    cout << dp[{n, n}] << '\n';
}

int main()
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