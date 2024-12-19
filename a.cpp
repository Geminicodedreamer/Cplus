#include <bits/stdc++.h>

using namespace std;

int maxcoin(vector<vector<int>> &piles, int k)
{
    int n = piles.size();

    vector<vector<int>> prefixSums(n);
    for (int i = 0; i < n; ++i)
    {
        prefixSums[i].push_back(0);
        for (int coin : piles[i])
        {
            prefixSums[i].push_back(prefixSums[i].back() + coin);
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= k; ++j)
        {
            dp[i][j] = dp[i - 1][j];
            for (int x = 1; x < prefixSums[i - 1].size() && x <= j; ++x)
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - x] + prefixSums[i - 1][x]);
            }
        }
    }

    return dp[n][k];
}

// int main()
// {
//     vector<vector<int>> piles = {{100}, {100}, {100}, {100}, {100}, {100}, {1, 1, 1, 1, 1, 1, 700}};
//     int k = 7;

//     cout << "最大硬币面值和: " << maxcoin(piles, k) << endl;
//     system("pause");
//     return 0;
// }

#include <iostream>
#include <vector>
using namespace std;

// 判断 Alice 是否能获胜的函数
bool canAliceWin(int n, vector<int> &dp)
{
    if (n == 1)
        return false;

    if (dp[n] != -1)
        return dp[n];

    for (int i = 1; i < n; ++i)
    {
        if (!canAliceWin(i - 1, dp) || !canAliceWin(n - i, dp))
        {
            dp[n] = true;
            return true;
        }
    }

    dp[n] = false;
    return false;
}

bool isAliceWinner(int n)
{
    vector<int> dp(n + 1, -1);
    return canAliceWin(n, dp);
}

int main()
{
    int n;

    while (cin >> n)
    {
        cout << "请输入 n 的值: ";
        cout << isAliceWinner(n) << '\n';
    }

    system("pause");
    return 0;
}


