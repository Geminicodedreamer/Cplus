#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
const int N = 200010;

struct Node
{
    int l, r;
    int v;
} tr[N * 50];
int n, q;
int root[N], idx;
PII seg[N];

void pushup(int u)
{
    tr[u].v = tr[tr[u].l].v + tr[tr[u].r].v;
}

int build(int u, int l, int r, int k)
{
    int p = ++idx;
    tr[p] = tr[u];
    if (l == r)
    {
        tr[p].v++;
        return p;
    }
    int mid = l + r >> 1;
    if (k <= mid)
        tr[p].l = build(tr[u].l, l, mid, k);
    else
        tr[p].r = build(tr[u].r, mid + 1, r, k);
    pushup(p);
    return p;
}

int query(int u, int l, int r, int x, int y)
{
    if (!u)
        return 0;
    if (l >= x && r < y)
        return tr[u].v;
    int mid = l + r >> 1;
    int res = 0;
    if (x <= mid)
        res += query(tr[u].l, l, mid, x, y);
    if (y > mid)
        res += query(tr[u].r, mid + 1, r, x, y);
    return res;
}

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> seg[i].first >> seg[i].second;

    sort(seg + 1, seg + 1 + n);

    for (int i = 1; i <= n; i++)
        root[i] = build(root[i - 1], 1, n, seg[i].second);

    while (q--)
    {
        int a, b;
        cin >> a >> b;
        if (a == b || seg[1].first > b)
        {
            cout << 0 << '\n';
            continue;
        }
        int l = 1, r = n;
        if (a < b)
        {
            while (l < r)
            {
                int mid = l + r + 1 >> 1;
                if (seg[mid].first <= a)
                    l = mid;
                else
                    r = mid - 1;
            }
            cout << query(root[l], 1, n, a, b - 1) << '\n';
        }
        else
        {
            while (l < r)
            {
                int mid = l + r >> 1;
                if (seg[mid].first > b)
                    r = mid;
                else
                    l = mid + 1;
            }
            int r1 = r;
            l = 1, r = n;
            while (l < r)
            {
                int mid = l + r + 1 >> 1;
                if (seg[mid].first <= a)
                    l = mid;
                else
                    r = mid - 1;
            }
            int l1 = l;
            cout << l1 << ' ' << r1 << '\n';
            cout << n - query(root[l1], 1, n, a, N) << ' ' << query(root[r1], 1, n, a, N) << '\n';
        }
    }
    return 0;
}
