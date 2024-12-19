#include <bits/stdc++.h>
using namespace std;

vector<int> path;

void find(vector<vector<int>> g, int u, int y)
{
    if (u == y)
    {
        for (auto it : path)
            if (it != path.back())
                cout << it << " -> ";
            else
                cout << it;
        cout << endl;
        return;
    }

    for (auto it : g[u])
    {
        if (it != 0)
        {
            path.push_back(it);
            find(g, it, y);
            path.pop_back();
        }
    }
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;
            g[i].push_back(x);
        }

    int x, y;
    cin >> x >> y;
    path.push_back(x);
    find(g, x, y);

    return 0;
}