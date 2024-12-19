#include <bits/stdc++.h>

using namespace std;
constexpr int N = 100010, M = 500010, len = 556;

int T;
int n, m, a[N];
int ans[M], w[1000][1000];

struct Query // 询问
{
    int x, y, m, f;
    int id; // id 是原先顺序编号
};

struct block
{
    int pre[1000];
} cnt[1000];
int cnt_pre[1000];

vector<Query> q[M];

void change(int x, int val)
{
    int sum = x / len;
    x %= len;
    if (x == 0)
        sum--, x += len;
    for (int i = x; i <= len; i++)
        cnt[sum].pre[i] += val;

    for (int i = sum; i <= len; i++)
        cnt_pre[i] += val;
}

void add(int x)
{ //向集合中插入 x
    change(x, 1);
    for (int j = 1; j < len; j++)
        w[j][x % j]++;
}

int ask(int l, int r)
{
    if (l > r)
        return 0;
    int lb = l / len;
    l %= len;
    int rb = r / len;
    r %= len;
    if (l == 0)
        lb--, l += len;
    if (r == 0)
        rb--, r += len;
    if (lb == rb)
        return cnt[lb].pre[r] - cnt[rb].pre[l - 1];
    int res = 0;
    res += cnt[lb].pre[len] - cnt[lb].pre[l - 1];
    res += cnt[rb].pre[r];
    res += cnt_pre[rb - 1] - cnt_pre[lb];
    return res;
}

int sum(int m, int k)
{
    int res = 0;
    if (m < len)
    {
        for (int j = 0; j <= k; j++)
            res += w[m][j];
        return res;
    }
    int l = m, r = m + k;
    res = ask(1, k);
    while (r < N)
    {
        res += ask(l, r);
        l += m, r += m;
    }
    if (l <= N)
        res += ask(l, N);
    return res;
}

int query(int m, int l, int r)
{
    if (l > r)
        return 0;
    return sum(m, r) - sum(m, l - 1);
}

void scan()
{
    for (int i = 1; i <= n; i++)
    {
        add(a[i]);
        for (int j = 0; j < q[i].size(); j++)
        {
            Query answer = q[i][j];
            int x = answer.x % answer.m, y = answer.y % answer.m;
            if (x == y)
                ans[answer.id] += 0;
            else if (x > y)
            {
                int l = answer.m - x, r = answer.m - y - 1;
                ans[answer.id] += answer.f * query(answer.m, l, r);
            }
            else
            {
                int l = answer.m - y, r = answer.m - x - 1;
                ans[answer.id] += answer.f * (i - query(answer.m, l, r));
            }
        }
    }
}

void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= m; i++)
    {
        int l, r, x, y, m;
        cin >> l >> r >> x >> y >> m;
        q[r].push_back({x, y, m, 1, i});
        q[l - 1].push_back({x, y, m, -1, i});
    }
    scan();

    for (int i = 1; i <= m; i++)
        cout << ans[i] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();

    return 0;
}
