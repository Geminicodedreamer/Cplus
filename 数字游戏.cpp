#include <bits/stdc++.h>

using namespace std;

int T;
int n;
double vmax, vmin, avg;

void solve()
{
    scanf("%d %lf %lf %lf", &n, &vmax, &vmin, &avg);
    if (vmax < vmin)
        puts("no");
    else
    {
        if (n == 1)
        {
            if (avg == vmax && avg == vmin)
                puts("yes");
            else
                puts("no");
        }
        else if (n == 2)
        {
            if (n * avg == vmax + vmin)
                puts("yes");
            else
                puts("no");
        }
        else
        {
            long double sum = n * avg - vmax - vmin;
            if (sum <= vmax * (n - 2) && sum >= vmin * (n - 2))
                puts("yes");
            else
                puts("no");
        }
    }
}

signed main()
{
    scanf("%d", &T);
    // T = 1;
    while (T--)
    {
        solve();
    }

    return 0;
}