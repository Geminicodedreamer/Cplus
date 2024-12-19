#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 11, MOD = 1e9 + 7;

int T;
int n, m, x;
char op[N];
int v[N], ans;
bool st[N];
vector<int> first, second;

int count(int x)
{
    int cnt = 0;
    while (x)
    {
        if (x & 1)
            cnt++;
        x >>= 1;
    }
    return cnt == 5;
}

void dfs(int S, int x, int u, vector<int> &c)
{
    if (u == 5)
    {
        c.push_back(x);
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        if (st[i] == 1)
            continue;

        if (S >> i & 1)
        {
            st[i] = 1;
            if (op[i] == '*')
                x = x * v[i] % MOD;
            if (op[i] == '+')
                x = (x + v[i]) % MOD;
            dfs(S, x, u + 1, c);
            st[i] = 0;
        }
    }
}

void solve()
{
    ans = MOD;
    cin >> n >> x;
    for (int i = 0; i < n; i++)
        cin >> op[i] >> v[i];

    int R = 1023;
    for (int S = 0; S < (1 << 10); S++)
    {
        if (!count(S))
            continue;
        first.clear(), second.clear();
        memset(st, 0, sizeof(st));
        dfs(S, x, 0, first);

        int w = 1;
        for (int i = 0; i < n; i++)
            if (!((S >> i) & 1) && op[i] == '*')
                w = w * v[i] % MOD;

        for (auto &it : first)
        {
            it = it * w % MOD;
        }

        dfs(S ^ R, 0, 0, second);

        sort(first.begin(), first.end());
        sort(second.begin(), second.end());

        int p = 0;
        for (int j = second.size() - 1; j; j--)
        {
            ans = min(ans, second[j] + first[0]);
            while (p < first.size() && second[j] + first[p] < MOD)
                p++;
            ans = min(ans, (second[j] + first[p]) % MOD);
        }
    }

    cout << ans << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    // T = 1;
    while (T--)
    {
        solve();
    }

    return 0;
}
