#include <bits/stdc++.h>
using namespace std;
string solution(int n, const vector<int> &sums)
{
    int sum = 0;
    for (auto s : sums)
        sum += s;
    if (sum % (n - 1) != 0)
        return "Impossible";

    vector<int> ans;
    sort(sums.begin(), sums.end());

    for (int i = -sums[0] / 2; i <= sums[0] / 2; i++)
    {
        ans[0] = i;
        map<int, int> p;
        for (auto s : sums)
            p[s]++;
        int idx = 0;
        for (auto [k, v] : p)
        {
            if (!v)
                continue;
            ans[idx] = k - ans[0];
            int t;
            for (t = 0; t < idx; t++)
                if (p[ans[idx] + ans[t]])
                    p[ans[idx] + ans[t]]--;
                else
                    break;
            if (t == idx)
                idx++;
            else
                break;
        }
        if (idx >= n)
            break;
    }

    for (int i = 0; i < n; i++)
        cout << ans[i] << ' ';

    return "";
}

int main()
{
    // You can add more test cases here
    vector<int> sums1 = {1269, 1160, 1663};
    vector<int> sums2 = {1, 1, 1};
    vector<int> sums3 = {226, 223, 225, 224, 227, 229, 228, 226, 225, 227};
    vector<int> sums4 = {-1, 0, -1, -2, 1, 0, -1, 1, 0, -1};
    vector<int> sums5 = {79950, 79936, 79942, 79962, 79954,
                         79972, 79960, 79968, 79924, 79932};

    cout << (solution(3, sums1) == "383 777 886") << endl;
    cout << (solution(3, sums2) == "Impossible") << endl;
    cout << (solution(5, sums3) == "111 112 113 114 115") << endl;
    cout << (solution(5, sums4) == "-1 -1 0 0 1") << endl;
    cout << (solution(5, sums5) == "39953 39971 39979 39983 39989") << endl;

    return 0;
}