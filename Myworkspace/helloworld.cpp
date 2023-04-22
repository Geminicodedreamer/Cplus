#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <climits>
using namespace std;
const int N = 500010;
int n, q;
vector<pair<int, int>> qx, qy;
template <typename T> // 快读模板
inline T fastread(T &x)
{
    x = 0;
    T w = 1;
    char ch = 0;
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x = x * w;
}

int main()
{
    fastread(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        fastread(x), fastread(y);
        qx.push_back({x, i});
        qy.push_back({y, i});
    }
    sort(qx.begin(), qx.end());
    sort(qy.begin(), qy.end());
    fastread(q);
    while (q--)
    {
        int sx, tx, sy, ty;
        fastread(sx), fastread(tx), fastread(sy), fastread(ty);
        vector<int> ansx, ansy;
        for (auto it = lower_bound(qx.begin(), qx.end(), make_pair(sx, 0)); it != upper_bound(qx.begin(), qx.end(), make_pair(tx, INT_MAX)); it++)
            ansx.push_back((*it).second);
        for (auto it = lower_bound(qy.begin(), qy.end(), make_pair(sy, 0)); it != upper_bound(qy.begin(), qy.end(), make_pair(ty, INT_MAX)); it++)
            ansy.push_back((*it).second);
        sort(ansx.begin(), ansx.end());
        sort(ansy.begin(), ansy.end());
        vector<int> ans;
        set_intersection(ansx.begin(), ansx.end(), ansy.begin(), ansy.end(), back_inserter(ans));
        for (auto item : ans)
            printf("%d\n", item);
        puts("");
    }
    system("pause");
    return 0;
}
