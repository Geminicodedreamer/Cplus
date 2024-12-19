#include <bits/stdc++.h>

using namespace std;
const int N = 500010, M = 20000010;

int T;

typedef pair<int, int> PII;
int n, m;
int h[N], e[N], w[N], ne[N], idx;
int dist[N];
int p[N], f[N];
int res[N], k[N];
int st[N];
int a[N], b[N], lca[N];
vector<PII> query[N]; // first存查询的另外一个点，second存查询编号

struct path
{
    int id, W, f;
};
vector<path> q[N];
int ans[N];
int W[M];

void calc(int u, int f)
{
    W[w[u]]++;
    for (path it : q[u])
        ans[it.id] += W[it.W] * it.f;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == f)
            continue;
        calc(j, u);
    }
    W[w[u]]--;
}

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u, int fa)
{
    f[u] = fa;
    dist[u] = w[u] ^ dist[fa];
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa)
            continue;
        dfs(j, u);
    }
}

int find(int x)
{
    if (p[x] != x)
        p[x] = find(p[x]);
    return p[x];
}

void tarjan(int u)
{
    st[u] = 1;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            tarjan(j);
            p[j] = u;
        }
    }

    for (auto item : query[u])
    {
        int y = item.first, id = item.second;
        if (st[y] == 2)
        {
            int LCA = find(y);
            res[id] = dist[u] ^ dist[y] ^ w[LCA];
            lca[id] = LCA;
        }
    }

    st[u] = 2;
}

void solve()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    for (int i = 0; i < m; i++)
    {
        cin >> a[i] >> b[i] >> k[i];
        query[a[i]].push_back({b[i], i});
        query[b[i]].push_back({a[i], i});
    }

    for (int i = 1; i <= n; i++)
        p[i] = i;

    dfs(1, -1);

    tarjan(1);

    for (int i = 0; i < m; i++)
    {
        int W = res[i] ^ k[i];
        q[a[i]].push_back((path){i, W, 1});
        q[b[i]].push_back((path){i, W, 1});
        q[lca[i]].push_back((path){i, W, -1});
        q[f[lca[i]]].push_back((path){i, W, -1});
    }
    calc(1, -1);
    for (int i = 0; i < m; i++)
        cout << (ans[i] ? "Yes" : "No") << '\n';
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