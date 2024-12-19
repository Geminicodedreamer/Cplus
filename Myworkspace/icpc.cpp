#include <bits/stdc++.h>
using namespace std;
string str;
int a[] = {2, 3, 5, 7, 23, 37, 53, 73, 373};
int solve(string str)
{
    // cin >> str;
    if (str.size() < 3)
    {
        int n = (str[0] - '0');
        if (str.size() == 2)
            n = n * 10 + str[1] - '0';
        for (int i = 0; i < 9; i++)
            if (a[i] > n)
            {
                i ? printf("%d\n", a[i - 1]) : puts("-1");
                return 0;
            }
    }
    else if (str.size() == 3)
    {
        int n = (str[0] - '0') * 100 + (str[1] - '0') * 10 + str[2] - '0';
        if (n >= 373)
            puts("373");
        else
            puts("73");
    }
    else
    {
        puts("373");
    }
}

int main()
{
    cin >> str;
    solve(str);
    system("pause");
}