#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

#define x first
#define y second

typedef long long LL;
typedef pair<int, int> PII;

const int N = 1e5 + 10, M = 2e6 + 10, mod = 998244353;

int n, m, k;
int h[N], e[M], ne[M], idx;
int dfn[N];            // dfn[u]: dfs遍历到 u的时间
int low[N], timestamp; // low[u]: 从 u开始走所能遍历到的最小时间戳
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, Size[N];
int dout[N];
vector<int> g[N]; // 无向边转化为有向边
int s[N];
bool st[N];
unordered_map<string, int> ma;
LL res = 0, cnt = 0;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

LL qmi(LL a, int k)
{
    LL res = 1 % mod;
    while (k)
    {
        if (k & 1)
            res = res * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return res;
}

void tarjan(int u)
{
    low[u] = dfn[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        // 如果当前点在栈中
        // 注意栈中存的可能是树中几个不同分支的点,因为有横叉边存在
        // 栈中存的所有点，是还没搜完的点，同时都不是强连通分量的最高点
        // 这里表示当前强连通分量还没有遍历完，即栈中有值
        else if (in_stk[j])
            low[u] = min(low[u], dfn[j]);
    }

    // 找到该连通分量的最高点
    if (dfn[u] == low[u])
    {
        ++scc_cnt;
        int y;
        do
        {
            y = stk[top--];
            id[y] = scc_cnt;
            in_stk[y] = false;
            Size[scc_cnt]++;
        } while (y != u);
    }
}

void dfs_u(int u, int fa) // 无向边转化为有向边
{
    st[u] = true;
    for (int j : g[u])
    {
        if (j == fa)
            continue;
        if (ma.count(to_string(j) + "-" + to_string(u)))
            continue;

        add(u, j);
        ma[to_string(u) + "-" + to_string(j)] = 1;
        if (!st[j])
            dfs_u(j, u);
    }
}

bool vis[N];
void dfs(int u)
{
    st[u] = true;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];

        if (id[j] != id[u])
            s[j] += s[u];
        else
            s[j] = s[u];

        if (!st[j])
            dfs(j);
    }

    if (!dout[id[u]] && !vis[id[u]])
    {
        vis[id[u]] = 1;
        res = (res + qmi(k + 1, s[u])) % mod;
        cnt++;
    }
}

int main()
{
    memset(h, -1, sizeof h);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs_u(1, -1);

    tarjan(1);

    for (int i = 1; i <= n; i++)
        for (int j = h[i]; ~j; j = ne[j])
        {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b)
                dout[a]++; // a和 b不属于同一个强连通分量
        }

    for (int i = 1; i <= n; i++)
        s[i] = Size[id[i]];

    memset(st, 0, sizeof st);
    dfs(1);

    if (cnt >= 2)
        res = (res - cnt + mod) % mod;
    cout << res;
    return 0;
}
