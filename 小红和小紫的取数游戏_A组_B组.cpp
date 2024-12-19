#include <bits/stdc++.h>

using namespace std;
const int N = 100010, M = 1010, S = 1000010;

int T;
struct hash_table
{
    int d[M];
} px, pa[N];
long long x;
int n, a[N];
int primes[S], cnt;
bool st[S];

hash_table operator^(const hash_table a, const hash_table b)
{
    hash_table c;
    for (int i = 0; i < M; i++)
        c.d[i] = a.d[i] ^ b.d[i];
    return c;
}

bool operator!(const hash_table a)
{
    for (int i = 0; i < M; i++)
        if (a.d[i] != 0)
            return false;
    return true;
}

void get_prime()
{
    for (int i = 2; i <= S; i++)
    {
        if (!st[i])
            primes[cnt++] = i;
        for (int j = 0; primes[j] <= S / i; j++)
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

struct Node
{
    int l, r;
    hash_table v;
} tr[N * 4];

void pushup(int u)
{
    tr[u].v = tr[u << 1].v ^ tr[u << 1 | 1].v;
}

void build(int u, int l, int r)
{
    if (l == r)
    {
        tr[u] = {l, r, pa[l]};
    }
    else
    {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void solve()
{
    cin >> n >> x;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    get_prime();

    for (int i = 0; i < cnt; i++)
    {
        while (x % primes[i] == 0)
        {
            px.d[i]++;
            x /= primes[i];
        }
    }

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < cnt; i++)
        {
            while (a[j] % primes[i] == 0)
            {
                pa[j].d[i]++;
                a[j] /= primes[i];
            }
        }
    }

    // build(1, 1, n); // 建树
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // cin >> T;
    T = 1;
    while (T--)
    {
        solve();
    }

    return 0;
}