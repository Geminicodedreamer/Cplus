#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 10010;
int p[N];
signed main()
{
    p[0] = 1;
    for (int i = 1; i < N; i++)
        p[i] = p[i - 1] * 3;
    int x;
    cin >> x;
    int n = 1;
    while (3 * (p[n] - 1) / 2 < x)
        n++;
    n--;
    x -= 3 * (p[n] - 1) / 2 + 1;
    for (int i = n; i >= 0; i--)
    {
        int t = x / p[i];
        if (t == 0)
            cout << 2;
        else if (t == 1)
            cout << 3;
        else
            cout << 6;
        x -= t * p[i];
    }
    return 0;
}