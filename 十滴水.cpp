#include <bits/stdc++.h>
using namespace std;

int c, m, n;
map<int, map<int, int>::iterator> mp;
map<int, int> s;
int x, w;

void dfs(map<int, int>::iterator x)
{
    auto it = x;

    if (it == s.begin() && it == s.end())
    {
        s.erase(x);
        return;
    }

    bool flag_pre = (it == s.begin());
    bool flag_last = (it == s.end());

    auto pre = it;
    if (!flag_pre)
        pre--, pre->second++;

    it = x;
    auto last = it;
    if (!flag_last)
        last++, last->second++;
    s.erase(x);

    // for(auto [k , v] : s)
    //     cout << v << ' ';
    // cout <<  '\n';

    if (!flag_pre && pre->second >= 5)
        dfs(pre);
    else if (!flag_last && last->second >= 5)
        dfs(last);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> c >> m >> n;
    while (m--)
    {
        cin >> x >> w;
        mp[x] = s.insert({x, w}).first;
    }

    int k;
    while (n--)
    {
        cin >> k;
        s[k]++;
        if (s[k] >= 5)
            dfs(mp[k]);
        cout << s.size() << '\n';
    }
}