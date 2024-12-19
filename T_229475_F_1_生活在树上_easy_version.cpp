#include <bits/stdc++.h>

#define int unsigned long long

using namespace std;
const int N = 500010, M = 2 * N;

int T;
int n, m;
int e[M], ne[M], w[M], idx, h[N];
bool st[N];
int dist[N]; // 到根的异或距离（dist）

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u)
{
    if (st[u])
        return;
    st[u] = true;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        dist[j] = dist[u] ^ w[i];
        dfs(j);
    }
}

void solve()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    memset(dist, 0, sizeof dist);
    for (int i = 1; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    dfs(1); // 遍历整棵树求出dist

    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if ((dist[a] ^ dist[b]) == c)
            cout << "Yes" << '\n';
        else
            cout << "No" << '\n';
    }
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
