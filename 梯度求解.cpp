#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long

using namespace std;
const int N = 100010, MOD = 1e9 + 7;
string oper;
int n, m;
stack<vector<pair<map<string, int>, int>>> heap;
map<string, int> num;
map<string, int> p;

bool is_num(string x)
{
    for (auto s : x)
        if (!isdigit(s) && s != '-')
            return false;
    return true;
}

int qmi(int a, int b)
{
    int res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res % MOD;
}

int to_num(string x)
{
    int res = 0, flag = 1;
    for (auto s : x)
    {
        if (s == '-')
            flag = -1;
        else
            res = res * 10 + s - '0';
    }
    return res * flag;
}

void calc(string op)
{
    auto a = heap.top();
    heap.pop();
    auto b = heap.top();
    heap.pop();

    if (op == "+")
    {
        for (auto it : b)
            a.push_back(it);
        heap.push(a);
    }
    else if (op == "-")
    {
        for (auto it : a)
            b.push_back({it.first, -1ll * it.second});
        heap.push(b);
    }
    else
    {
        vector<pair<map<string, int>, int>> t;
        for (auto itb : b)
        {
            for (auto ita : a)
            {
                pair<map<string, int>, int> tmp;
                for (auto [k, v] : itb.first)
                {
                    tmp.first[k] = itb.first[k] + ita.first[k];
                }
                tmp.second = ita.second * itb.second % MOD;
                t.push_back(tmp);
            }
        }
        heap.push(t);
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        string s = "x" + to_string(i);
        p[s] = 0;
    }

    getline(cin, oper);
    getline(cin, oper);

    for (int i = 0; i < oper.size(); i++)
    {
        string x = "";
        while (oper[i] != ' ' && i < oper.size())
            x += oper[i++];

        if (x == "+" || x == "-" || x == "*")
            calc(x);
        else if (is_num(x))
        {
            vector<pair<map<string, int>, int>> c;
            c.push_back({p, to_num(x)});
            heap.push(c);
        }
        else
        {
            auto t = p;
            t[x]++;
            vector<pair<map<string, int>, int>> c;
            c.push_back({t, 1});
            heap.push(c);
        }
    }

    // auto t = heap.top();
    // for (auto [y, c] : t)
    // {
    //     for (auto [k, v] : y)
    //         cerr << k << ' ' << v << endl;
    //     cerr << "c " << c << '\n';
    // }

    while (m--)
    {
        int id;
        cin >> id;
        string x = "x" + to_string(id);
        for (int i = 1; i <= n; i++)
        {
            string x2 = "x" + to_string(i);
            int number;
            cin >> number;
            num[x2] = number;
        }

        // for (auto [y, c] : num)
        // {
        //     cerr << y << ' ' << c << '\n';
        // }

        int res = 0;

        for (auto t : heap.top())
        {
            auto it = t.first;
            int c = t.second;
            if (c == 0)
                continue;
            int k = c;
            for (auto y : it)
            {
                string w = y.first;
                int mi = y.second;
                // cout << w << ' ' << num[w] << ' ' << mi << '\n';
                if (x == w)
                {
                    if (mi == 0)
                    {
                        k = 0ll;
                        break;
                    }
                    else
                    {
                        k = k * qmi(num[w], mi - 1) % MOD;
                        k = k * mi % MOD;
                    }
                }
                else
                {
                    k = k * qmi(num[w], mi) % MOD;
                }
                // cout << k << '\n';
            }
            res = (res + k) % MOD;
        }
        cout << (res % MOD + MOD) % MOD << '\n';
    }

    return 0;
}