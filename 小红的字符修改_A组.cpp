#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1000010, MOD_1 = 1e9 + 7, MOD_2 = 1e9 + 9;
typedef pair<int, int> PII;
const PII P = {13331, 23333};

int n, q;
char s[N];
PII h[N], p[N];

PII operator+(PII a, PII b)
{
    int c1 = a.first + b.first, c2 = a.second + b.second;
    if (c1 >= MOD_1)
        c1 -= MOD_1;
    if (c2 >= MOD_2)
        c2 -= MOD_2;
    return {c1, c2};
}

PII operator-(PII a, PII b)
{
    int c1 = a.first - b.first, c2 = a.second - b.second;
    if (c1 < 0)
        c1 += MOD_1;
    if (c2 < 0)
        c2 += MOD_2;
    return {c1, c2};
}

PII operator*(PII a, PII b)
{
    return {a.first * b.first % MOD_1, a.second * b.second % MOD_2};
}

struct Node
{
    int l, r;
    PII v, sum;
} tr[N * 4];

void pushup(int u)
{
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void build(int u, int l, int r)
{
    if (l == r)
        tr[u] = {l, r, h[l], h[l]};
    else
    {
        int mid = l + r >> 1;
        tr[u] = {l, r};
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

PII query(int u, int l, int r)
{
    PII res = {0, 0};
    if (tr[u].l >= l && tr[u].r <= r)
        return tr[u].sum;

    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid)
        res = res + query(u << 1, l, r);
    if (r > mid)
        res = res + query(u << 1 | 1, l, r);
    return res;
}

void modify(int u, int x, char c)
{
    if (tr[u].l == x && tr[u].r == x)
    {
        tr[u].v = tr[u].sum = make_pair(c, c) * p[x];
        s[x] = c;
    }
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid)
            modify(u << 1, x, c);
        else
            modify(u << 1 | 1, x, c);
        pushup(u);
    }
}

signed main()
{
    cin >> n >> q;
    cin >> s + 1;
    p[0] = {1, 1};
    for (int i = 1; i <= n; i++)
    {
        p[i] = p[i - 1] * P;
        h[i] = make_pair(s[i], s[i]) * p[i];
    }

    build(1, 1, n);

    int op;
    while (q--)
    {
        cin >> op;
        if (op == 1)
        {
            char c;
            int x;
            cin >> x >> c;
            modify(1, x, c);
        }
        else if (op == 2)
        {
            signed l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            int u = abs(l1 - l2);
            if (query(1, l1, r1) == query(1, l2, r2) * p[u] || query(1, l1, r1) * p[u] == query(1, l2, r2))
                puts("Yes");
            else
                puts("No");
        }
    }
}
