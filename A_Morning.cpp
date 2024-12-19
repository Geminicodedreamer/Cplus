#include <bits/stdc++.h>

using namespace std;
const int N = 21;
struct Point
{
    int x, y;
    Point() { x = 0, y = 0; }
    Point(int _x, int _y) : x(_x), y(_y) {}
    bool operator<(const Point &t) const
    {
        if (x == t.x)
            return y < t.y;
        return x < t.x;
    }
};

int n, m, k, cnt;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
bool st[N][N], g[N][N];
set<vector<Point>> s;

void bfs()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (st[i][j] || !g[i][j])
                continue;
            cnt++;
            queue<Point> q;
            q.push({i, j});
            st[i][j] = true;
            while (q.size())
            {
                auto t = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int tx = t.x + dx[k], ty = t.y + dy[k];
                    if (tx < 0 || tx >= n || ty < 0 || ty >= m)
                        continue;
                    if (st[tx][ty] || !g[tx][ty])
                        continue;
                    q.push({tx, ty});
                    st[tx][ty] = true;
                }
            }
        }
}

void move_to_O(vector<Point> &x)
{
    int mx = 0x3f3f3f3f, my = 0x3f3f3f3f;
    vector<Point> res;
    for (auto &it : x)
    {
        mx = min(mx, it.x);
        my = min(my, it.y);
    }
    for (auto &it : x)
    {
        it.x -= mx;
        it.y -= my;
    }
}

void rev(vector<Point> &x)
{
    move_to_O(x);
    int mx = 0, my = 0;
    for (auto it : x)
    {
        mx = max(mx, it.x);
        my = max(my, it.y);
    }
    mx = max(mx, my);
    for (auto &it : x)
    {
        int tx = it.x, ty = it.y;
        it.x = ty, it.y = mx - tx;
    }
    move_to_O(x);
    sort(x.begin(), x.end());
}

vector<Point> rey(vector<Point> x)
{
    vector<Point> res;
    for (auto it : x)
        res.push_back(Point(it.x, -it.y));
    move_to_O(res);
    sort(res.begin(), res.end());
    return res;
}

vector<Point> rex(vector<Point> x)
{
    vector<Point> res;
    for (auto it : x)
        res.push_back(Point(-it.x, it.y));
    move_to_O(res);
    sort(res.begin(), res.end());
    return res;
}

bool check(vector<Point> x)
{
    if (s.count(x))
        return true;
    for (int i = 0; i < 3; i++)
    {
        rev(x);
        if (s.count(x))
            return true;
    }
    return false;
}

void count(vector<Point> x, int k)
{
    if (k < 0)
        return;
    move_to_O(x);
    int mx = 0, my = 0;
    for (auto it : x)
    {
        mx = max(mx, it.x);
        my = max(my, it.y);
    }

    if ((mx >= n || my >= m) && (mx >= m || my >= n))
        return;
    if (check(x) || check(rex(x)) || check(rey(x)))
        return;
    s.insert(x);

    set<Point> ss;
    for (auto it : x)
        ss.insert(it);
    for (auto it : x)
        for (int j = 0; j < 4; j++)
        {
            int tx = it.x + dx[j], ty = it.y + dy[j];
            if (ss.count(Point(tx, ty)))
                continue;
            vector<Point> t = x;
            t.push_back(Point(tx, ty));
            sort(t.begin(), t.end());
            move_to_O(t);
            count(t, k - 1);
        }
}

void solve()
{
    cin >> k >> n >> m;
    cnt = 0;
    s.clear();
    memset(st, 0, sizeof st);
    memset(g, 0, sizeof g);

    vector<Point> p;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> g[i][j];
            if (g[i][j])
                p.push_back(Point(i, j));
        }

    bfs();

    if (cnt == 0 && k == 0)
    {
        cout << 0 << '\n';
        return;
    }

    if (cnt == 0)
    {
        k--;
        g[0][0] = 1;
        p.push_back(Point(0, 0));
    }

    if (cnt >= 2)
    {
        cout << -1 << '\n';
        return;
    }

    sort(p.begin(), p.end());
    count(p, k);
    cout << s.size() << '\n';
}

int main()
{
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}