#include <bits/stdc++.h>

using namespace std;
const int N = 100010;

int T;

int n, m;
int w[N], p[N], s[N];
int ans[N], cnt;
vector<int> val[N];
bool st[N];
struct edge
{
    int u, v;
} edge[N];

struct query
{
    int op, u;
} q[N];

int find(int x)
{
    if (x != p[x])
        p[x] = find(p[x]);
    return p[x];
}

void add(int a, int b)
{
    int pa = find(a), pb = find(b);
    if (pa != pb)
    {
        p[pa] = pb;
        s[pb] += s[pa];
        s[pa] = 0;
    }
}

void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    for (int i = 1; i < n; i++)
        cin >> edge[i].u >> edge[i].v;

    for (int i = 1; i <= m; i++)
    {
        cin >> q[i].op >> q[i].u;
        if (q[i].op == 1)
            st[q[i].u] = true;
        else if (q[i].op == 2)
        {
            int v;
            cin >> v;
            val[q[i].u].push_back(w[q[i].u]);
            w[q[i].u] = v;
        }
    }

    for (int i = 1; i <= n; i++)
        s[i] = w[i], p[i] = i;

    for (int i = 1; i < n; i++) // 构建最后操作结束后的森林
    {
        if (!st[i])
            add(edge[i].u, edge[i].v);
    }

    for (int i = m; i; i--)
    {
        if (q[i].op == 1) // 恢复断边
            add(edge[q[i].u].u, edge[q[i].u].v);
        else if (q[i].op == 2)
        {
            int u = q[i].u;
            int now = val[u].back();
            val[u].pop_back();
            s[find(u)] += now - w[u];
            w[u] = now;
        }
        else
            ans[++cnt] = s[find(q[i].u)];
    }

    for (int i = cnt; i; i--)
        cout << ans[i] << '\n';
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