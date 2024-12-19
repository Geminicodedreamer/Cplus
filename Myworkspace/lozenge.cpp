#include <bits/stdc++.h>
using namespace std;
int n;
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (abs(n / 2 - i) + abs(n / 2 - j) <= n / 2)
                cout << '*';
            else
                cout << " ";
        cout << '\n';
    }
    return 0;
}