#include <bits/stdc++.h>

#define int long long

using namespace std;
const int N = 200010;

typedef pair<int, int> PII;
int n, X, Y;
int T;
bool vis[N];

struct Node
{
    int x, y, id;
} a[N * 2];

void solve()
{
    cin >> n >> X >> Y;
    for (int i = 1; i <= n; i++)
    {
        int x, y, l;
        cin >> x >> y >> l;
        a[i] = {x - X, Y - y, i};
        a[i + n] = {x + l - X, Y - y, -i}; // 用于区分左右端点
    }

    sort(a + 1, a + 2 * n + 1, [&](Node p, Node q)
         { return q.y * p.x < q.x * p.y; });

    set<PII> st;
    Node last = {-1, 1, 0};
    for (int i = 1; i <= n * 2; i++)
    {
        auto it = a[i];
        if (it.x * last.y != it.y * last.x)
        {
            if (st.size())
                vis[st.begin()->second] = true;
            last = it;
        }
        if (it.id > 0)
            st.insert({it.y, it.id});
        else
            st.erase({it.y, -it.id});
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans += vis[i];
    cout << ans << '\n';
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