#include <bits/stdc++.h>

using namespace std;
#define int long long
const int N = 1e5, M = 1e9;
signed main()
{
    srand(time(0));
    int n, k, x;
    n = rand() % N;
    k = rand() % M;
    x = rand() % M;
    int a[n + 1];
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % M;
    }
    cout << n << " " << k << " " << x << endl;
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
}