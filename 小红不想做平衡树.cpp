#include <bits/stdc++.h>
#define int long long

using namespace std;
const int N = 2000010;

int T;
int n;
int a[N];
vector<int> v;

void solve()
{
    cin >> n;
    v.push_back(1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int flag = 1;
    if (a[1] > a[2])
        flag = 0;
    for (int i = 2; i < n; i++)
    {
        if (a[i] > a[i - 1] && a[i] > a[i + 1])
            v.push_back(i);
        else if (a[i] < a[i - 1] && a[i] < a[i + 1])
            v.push_back(i);
    }
    v.push_back(n);
    int len = v.size(), ans = 0;
    for (int i = 1; i < len; i++)
    {
        int m = v[i] - v[i - 1] + 1;
        ans += m * (m + 1) / 2;
    }
    ans -= len - 2;
    for (int i = flag; i < len - 2; i += 2)
    {
        // v[i],v[i+1],v[i+2]
        for (int j = v[i + 1] - 1; j >= v[i]; j--)
            if (a[j] < a[v[i + 1] + 1])
                ans += (v[i + 2] - v[i + 1]);
    }
    for (int i = flag ^ 1; i < len - 2; i += 2)
    {
        // v[i],v[i+1],v[i+2]
        for (int j = v[i + 1] + 1; j <= v[i + 2]; j++)
            if (a[j] > a[v[i + 1] - 1])
                ans += (v[i + 1] - v[i]);
    }
    for (int i = flag ^ 1; i < len - 3; i += 2)
    {
        // v[i],v[i+1],v[i+2],v[i+3]
        if (a[v[i + 1]] < a[v[i + 2] + 1] && a[v[i + 2]] > a[v[i + 1] - 1])
            ans += (v[i + 1] - v[i]) * (v[i + 3] - v[i + 2]);
    }
    printf("%lld", ans);
    // case1: (a,b) -> n=b-a+1,ans+=n(n+1)/2; ans-=v.size()-2
    // case2: (a,b,c) [down,up] -> ans+=(c-b)*cnt -> if a[i]<a[b+1]
    // case3: (a,b,c,d) [up,down,up]
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