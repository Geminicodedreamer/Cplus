#include <bits/stdc++.h>

using namespace std;

const int N = 1000010, M = 1010;

char p[N], s[M];
int n, m;
int location[110];
int suf[M];
bool pre[M];
void presuf()
{
    memset(suf, -1, sizeof(suf));
    for (int i = 0; i < m - 1; i++)
    {
        int j = i;
        int k = 0;
        while (j >= 0 && s[j] == s[m - 1 - k])
        {
            j--, k++;
            suf[k] = j + 1;
        }
        if (j == -1)
            pre[k] = true;
    }
}

int goodsuf(int r)
{
    int k = m - 1 - r;
    if (suf[k] != -1)
        return r - suf[k] + 1;
    for (int j = r + 2; j < m; j++)
        if (pre[m - j])
            return j;
    return m;
}

int BM()
{
    cin >> p >> s;
    n = strlen(p), m = strlen(s);
    presuf();
    for (int i = 0; i < m; i++)
        location[s[i] - 'a'] = i; // 记录每个字符的最后位置

    int l = 0;
    while (l <= n - m)
    {
        int r;
        for (r = m - 1; r >= 0; r--) // 从后向前匹配
            if (!r && s[r] == p[l + r])
                return l;
            else if (s[r] != p[l + r])
                break;

        int x = r - location[p[l + r] - 'a'];
        int y = 0;
        if (r < m - 1)
            y = goodsuf(r);
        l += max(x, y);
    }
    return -1;
}

int ne[N];
int KMP()
{
    cin >> p + 1 >> s + 1;
    n = strlen(p + 1), m = strlen(s + 1);
    for (int i = 2, j = 0; i <= m; i++)
    {
        while (s[i] != s[j + 1] && j)
            j = ne[j];
        if (s[i] == s[j + 1])
            j++;
        ne[i] = j;
    }

    for (int i = 1, j = 0; i <= n; i++)
    {
        while (p[i] != s[j + 1] && j)
            j = ne[j];
        if (p[i] == s[j + 1])
            j++;
        if (j == m)
            return i - m;
    }
}

int main()
{
    cout << BM() << endl
         << KMP() << endl;
    system("pause");
    return 0;
}