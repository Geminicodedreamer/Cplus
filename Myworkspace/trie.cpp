#include <iostream>
#include <algorithm>
#include <cmath>
#define int long long
using namespace std;
const int N = 500010;

struct Tree
{
    int l, r;
    int xmin, xmax, ymin, ymax;
} tr[N * 4];
pair<int, int> q[N];

void pushup(Tree &u, Tree &l, Tree &r)
{
    u.xmax = max(l.xmax, r.xmax);
    u.xmin = min(l.xmin, r.xmin);
    u.ymax = max(l.ymax, r.ymax);
    u.ymin = min(l.ymin, r.ymin);
}

void pushup(int u)
{
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r)
{
    if (l == r)
        tr[u] = {l, r, q[l].first, q[l].first, q[l].second, q[l].second};
    else
    {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}
int sx, tx, sy, ty;
void query(int u)
{
    if (tr[u].xmax <= tx && tr[u].xmin >= sx && tr[u].ymax <= ty && tr[u].ymin >= sy)
    {
        for (int i = tr[u].l; i <= tr[u].r; i++)
            printf("%lld\n", i - 1);
        return;
    }
    else if (tr[u].xmax < sx || tr[u].xmin > tx || tr[u].ymax < sy || tr[u].ymin > ty)
        return;
    else
    {
        if (tr[u].l == tr[u].r)
            return;
        int mid = tr[u].l + tr[u].r >> 1;
        query(u << 1);
        query(u << 1 | 1);
    }
}

signed main()
{
    int n;
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &q[i].first, &q[i].second);
    build(1, 1, n);

    int m;
    scanf("%lld", &m);
    while (m--)
    {
        scanf("%lld%lld%lld%lld", &sx, &tx, &sy, &ty);
        query(1);
        puts("");
    }

    system("pause");
    return 0;
}