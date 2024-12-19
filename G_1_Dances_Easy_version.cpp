#include <bits/stdc++.h>
#include <queue>
#define int long long

using namespace std;
const int N = 100010;
int n, k, x;
int a[N];
bool check(int m)
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] - m <= 0)
            continue;
        cnt += (a[i] - m) / x + ((a[i] - m) % x != 0);
    }
    // cout << m << ' ' << cnt << '\n';
    return cnt <= k;
}

signed main()
{
    cin >> n >> k >> x;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int l = -1e12, r = 1e12;
    while (l < r)
    {
        // cout << l << ' ' << r << '\n';
        int mid = l + r >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    cout << r << '\n';
    return 0;
}