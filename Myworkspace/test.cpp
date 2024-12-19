#include <bits/stdc++.h>

using namespace std;

const int N = 200010, M = N * 2;

struct Query
{
    int l, r;
} q[N];
int n, len;
int h[N], e[M], ne[M], col[M], c[M], idx;
int s1[N], s2[N], l[N], r[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int get_len(int x)
{
    return x / len;
}

int cidx = 0;
void dfs(int u)
{
    col[++cidx] = c[u];
    l[u] = cidx;
    for (int i = h[u]; ~i; i = ne[i])
        dfs(e[i]);
    r[u] = cidx;
}

int main()
{
    cin >> n;
    len = sqrtl(n);
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++)
    {
        int father;
        cin >> col[i] >> father;
        if (i != 1)
            add(father, i);
    }
    dfs(1);

    for (int i = 1; i <= n; i++)
    {
        q[i - 1] = {l[i], r[i]};
    }
    sort(q, q + n, [&](const Query &a, const Query &b)
         {
        if(get_len(a.l) != get_len(b.l))
            return a.l < b.l;
        return a.r < b.r; });

    int ans = 0, cnt = 0;
    for (int i = 0, ll = 0, rr = 0; i < n; i++)
    {
        while (ll > q[i].l)
        {
            ll--;
            s2[s1[col[ll]]] && s2[s1[col[ll]]]--;
            s1[col[ll]]++;
            s2[s1[col[ll]]]++;
            s1[col[ll]] == 1 && cnt++;
        }
        while (rr < q[i].r)
        {
            rr++;
            s2[s1[col[rr]]] && s2[s1[col[rr]]]--;
            s1[col[rr]]++;
            s2[s1[col[rr]]]++;
            s1[col[rr]] == 1 && cnt++;
        }
        while (ll < q[i].l)
        {
            s2[s1[col[ll]]] && s2[s1[col[ll]]]--;
            s1[col[ll]]--;
            s2[s1[col[ll]]]++;
            s1[col[ll]] || cnt--;
            ll++;
        }
        while (rr > q[i].r)
        {
            s2[s1[col[rr]]] && s2[s1[col[rr]]]--;
            s1[col[rr]]--;
            s2[s1[col[rr]]]++;
            s1[col[rr]] || cnt--;
            rr--;
        }
        int length = rr - ll + 1;
        length % cnt == 0 && s2[length / cnt] == cnt &&ans++;
    }
    cout << ans;
    return 0;
}