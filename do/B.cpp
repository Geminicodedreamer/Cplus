#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 998244353;
const int MAXN = 100010;  //点数
const int MAXM = 2000010; //边数

// ----------- tarjan 无向图 缩点 -----------
struct Edge
{
    int to, next;
    int cut; //是否被标记
} edge[MAXM];
int head[MAXN], tot;
int Low[MAXN], DFN[MAXN], Stack[MAXN], Belong[MAXN]; //数组的值是1~lock
int Index, top;
int block; //边双连通块数
bool Instack[MAXN];
int bridge;
void addedge(int u, int v)
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    edge[tot].cut = false;
    head[u] = tot++;
}
void Tarjan(int u, int pre)
{
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    int pre_cnt = 0;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        v = edge[i].to;
        if (v == pre && pre_cnt == 0)
        {
            pre_cnt++;
            continue;
        }
        if (!DFN[v])
        {
            Tarjan(v, u);
            Low[u] = min(Low[u], Low[v]);
            if (Low[v] > DFN[u])
            {
                bridge++;
                edge[i].cut = true;
                edge[i ^ 1].cut = true;
            }
        }
        else if (Instack[v] && Low[u] > DFN[v])
        {
            Low[u] = DFN[v];
        }
    }
    if (Low[u] == DFN[u])
    {
        block++;
        do
        {
            v = Stack[--top];
            Instack[v] = false;
            Belong[v] = block;
        } while (v != u);
    }
}
void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
}
// ----------- tarjan 无向图 缩点 -----------
int n, m, k;
int u, v;
vector<int> ve[MAXN];
int num[MAXN];
ll quickp(ll a, ll p)
{
    ll res = 1;
    while (p)
    {
        if (p & 1)
        {
            res = res * a % mod;
        }
        a = a * a % mod;
        p >>= 1;
    }
    return res;
}
ll dfs(int u, int p)
{
    ll res = 0;
    for (auto v : ve[u])
    {
        if (v == p)
        {
            continue;
        }
        res = (res + dfs(v, u)) % mod;
    }
    if (!res)
    {
        return quickp(k + 1, num[u]);
    }
    return res * quickp(k + 1, num[u]) % mod;
}
void solve()
{
    memset(DFN, 0, sizeof(DFN));
    memset(Instack, false, sizeof(Instack));
    Index = top = block = 0;

    Tarjan(1, 0);
    for (int i = 1; i <= n; ++i)
    {
        ++num[Belong[i]];
    }
    // 构建缩点后的 树
    for (int i = 1; i <= n; i++)
    {
        for (int j = head[i]; j != -1; j = edge[j].next)
        {
            int v = edge[j].to;
            if (Belong[i] != Belong[v])
            {
                ve[Belong[i]].push_back(Belong[v]);
            }
        }
    }

    ll ans = dfs(Belong[1], -1);

    if (ve[Belong[1]].size())
    { // 要去除 子树 全部没有染色时的情况，避免 重复计算
        ans = (ans + (mod - (ve[Belong[1]].size() - 1) * quickp(k + 1, num[Belong[1]]) % mod)) % mod;
    }

    printf("%lld\n", ans);
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    init();
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    solve();

    return 0;
}