#include <bits/stdc++.h>
using namespace std;
int main()
{
    int l;
    cin >> l;
    int sum = 0;
    for (int i = 1; i <= l + 1; i++)
        sum += i;

    double res = 0.0;
    for (int i = 1; i <= l + 1; i++)
    {
        res += (double)i * (l--) / sum;
    }

    cout << fixed << setprecision(7) << res << '\n';
    system("pause");
    return 0;
}