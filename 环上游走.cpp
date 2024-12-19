#include <bits/stdc++.h>

using namespace std;
const int N = 81;

int T;
int n;
int res;
bool w[N];

void dfs(int x, int u)
{
    if (u == n)
    {
        res++;
        return;
    }

    int l;
    if (x + u <= n)
        l = x + u;
    else
        l = x + u - n;
    int r;
    if (x - u <= 0)
        r = x - u + n;
    else
        r = x - u;
    if (w[l] && w[r])
        return;
    if (!w[l])
    {
        w[l] = 1;
        dfs(l, u + 1);
        w[l] = 0;
    }
    if (!w[r])
    {
        w[r] = 1;
        dfs(r, u + 1);
        w[r] = 0;
    }
}

void solve()
{
    scanf("%d", &n);
    res = 0;
    memset(w, 0, sizeof w);
    w[1] = 1;
    dfs(1, 1);
    printf("%d\n", res);
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        solve();
    }

    return 0;
}