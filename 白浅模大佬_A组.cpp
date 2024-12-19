#pragma GCC optimize(2)

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100010;

int T;

struct Block
{
    int n;
    int len;
    bool f;

    void init(int n)
    {
        n = n, len = (int)sqrt(n), f = len != (n / (int)sqrt(n));
    }

    int get(int x)
    {
        return (x <= len ? x
                         : (len << 1) - n / x + f) -
               1;
    }

    int get_l(int id)
    {
        if (id < 0 || id > get(n))
        {
            return -1;
        }
        return id + 1 <= len ? id + 1 : n / (get(n) - id + 2) + 1;
    }

    int get_r(int id)
    {
        if (id < 0 || id > get(n))
        {
            return -1;
        }
        return n / (n / get_l(id));
    }
} block;

int n, m, c;
int w[N];

struct TreeNode
{
    int sum, scdx, less, x, lazy;
} tr[N * 4];

void pushdown(int u, int L, int R)
{
    if (tr[u].lazy)
    {
        tr[u].less -= tr[u].lazy;
        tr[u].sum -= tr[u].scdx * tr[u].lazy;
        if (L == R)
            tr[u].x += tr[u].lazy;
        else
            tr[u << 1].lazy += tr[u].lazy, tr[u << 1 | 1].lazy += tr[u].lazy;

        tr[u].lazy = 0;
    }
}

void pushup(int u, int L, int R)
{
    int mid = L + R >> 1;
    pushdown(u << 1, L, mid);
    pushdown(u << 1 | 1, mid + 1, R);
    tr[u].less = min(tr[u << 1].less, tr[u << 1 | 1].less);
    tr[u].scdx = tr[u << 1].scdx + tr[u << 1 | 1].scdx;
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void build(int u, int l, int r)
{
    if (l == r)
    {
        tr[u].x = w[l];
        if (tr[u].x <= c)
        {
            tr[u].less = block.get_r(block.get(tr[u].x)) - tr[u].x;
            tr[u].scdx = c / tr[u].x;
            tr[u].sum = c - tr[u].scdx * tr[u].x;
        }
        else
        {
            tr[u].less = (1 << 30);
            tr[u].scdx = 0;
            tr[u].sum = c;
        }
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u, l, r);
}

void modify(int u, int L, int R, int l, int r, int v)
{
    pushdown(u, L, R);
    if (L >= l && R <= r)
    {
        if (tr[u].less >= v)
        {
            tr[u].lazy += v;
            return;
        }
        if (L == R)
        {
            tr[u].x += v;
            if (tr[u].x <= c)
            {
                tr[u].less = block.get_r(block.get(tr[u].x)) - tr[u].x;
                tr[u].scdx = c / tr[u].x;
                tr[u].sum = c - tr[u].scdx * tr[u].x;
            }
            else
            {
                tr[u].less = (1 << 30);
                tr[u].scdx = 0;
                tr[u].sum = c;
            }
            return;
        }
        int mid = L + R >> 1;
        if (l <= mid)
            modify(u << 1, L, mid, l, r, v);
        if (r > mid)
            modify(u << 1 | 1, mid + 1, R, l, r, v);
        pushup(u, L, R);
        return;
    }
    int mid = L + R >> 1;
    if (l <= mid)
        modify(u << 1, L, mid, l, r, v);
    if (r > mid)
        modify(u << 1 | 1, mid + 1, R, l, r, v);
    pushup(u, L, R);
}

int query(int u, int L, int R, int l, int r)
{
    pushdown(u, L, R);
    if (l <= L && r >= R)
        return tr[u].sum;
    int mid = L + R >> 1;

    if (r <= mid)
        return query(u << 1, L, mid, l, r);
    else if (l > mid)
        return query(u << 1 | 1, mid + 1, R, l, r);
    else
        return query(u << 1, L, mid, l, r) + query(u << 1 | 1, mid + 1, R, l, r);
}

signed main()
{
    scanf("%lld%lld%lld", &n, &m, &c);
    block.init(c);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &w[i]);

    build(1, 1, n);

    int op, l, r, x;
    while (m--)
    {
        scanf("%lld%lld%lld", &op, &l, &r);
        if (op == 1)
        {
            scanf("%lld", &x);
            modify(1, 1, n, l, r, x);
        }
        else
        {
            printf("%lld\n", query(1, 1, n, l, r));
        }
    }
    return 0;
}
