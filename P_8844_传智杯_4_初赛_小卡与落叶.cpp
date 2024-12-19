#include <bits/stdc++.h>

using namespace std;
const int N = 100010, M = 2 * N;

int T;
int n, m;
int depth[N];
vector<int> dep[N];  // 每个深度的节点
int L[N], R[N], tot; // 每棵树的子树dfs范围
int e[M], ne[M], idx, h[N];
int ans[N], cnt;

struct Node
{
    int l, r, v;
} tr[N * 8];

struct Query
{
    int id, d, x;
} q[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u, int fa)
{
    L[u] = ++tot;
    dep[depth[u]].push_back(u);
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa)
            continue;
        depth[j] = depth[u] + 1;
        dfs(j, u);
    }
    R[u] = ++tot;
}

void pushup(int u)
{
    tr[u].v = tr[u << 1].v + tr[u << 1 | 1].v;
}

void build(int u, int l, int r)
{
    tr[u] = {l, r};
    if (l == r)
        return;
    else
    {
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    }
}

void modify(int u, int x)
{
    if (tr[u].l == x && tr[u].r == x)
        tr[u].v++;
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid)
            modify(u << 1, x);
        else
            modify(u << 1 | 1, x);
        pushup(u);
    }
}

int query(int u, int l, int r)
{
    if (tr[u].l >= l && tr[u].r <= r)
        return tr[u].v;
    int res = 0;
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid)
        res += query(u << 1, l, r);
    if (r > mid)
        res += query(u << 1 | 1, l, r);
    return res;
}

void solve()
{
    memset(h, -1, sizeof h);
    cin >> n >> m;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
    }

    depth[1] = 1;
    dfs(1, -1);

    build(1, 1, tot);

    int last_dep = n;
    while (m--)
    {
        int op, x;
        cin >> op >> x;
        if (op == 1)
            last_dep = x;
        else
            q[++cnt] = {cnt, last_dep, x};
    }

    sort(q + 1, q + 1 + cnt, [&](Query a, Query b)
         { return a.d > b.d; });

    int l = n;
    for (int i = 1; i <= cnt; i++)
    {
        while (l >= q[i].d)
        {
            for (int u : dep[l])
                modify(1, L[u]);
            l--;
        }
        ans[q[i].id] = query(1, L[q[i].x], R[q[i].x]);
    }

    for (int i = 1; i <= cnt; i++)
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