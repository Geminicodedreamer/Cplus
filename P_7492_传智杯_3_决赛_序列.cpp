#include <bits/stdc++.h>

#define x first
#define y second

using namespace std;
const int N = 100010;

int T;

int n, q;
struct Node
{
    int l, r;
    int v, k, sum, ls, rs;
} tr[N * 4];

int w[N];

void pushup(int u)
{
}

void build(int u, int l, int r)
{
}

int query(int u, int l, int r)
{
}

void modify(int u, int l, int r, int k)
{
}

void solve()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    build(1, 1, n);
    while (q--)
    {
        int op, l, r, x;
        cin >> op >> l >> r;
        if (op == 1)
            cout << query(1, l, r);
        else if (op == 2)
        {
            cin >> x;
            modify(1, l, r, x);
        }
    }
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