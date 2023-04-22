

// #include <bits/stdc++.h>

// using namespace std;

// const int N = 110;
// double p[N], q[N];
// double f[N][N], w[N][N];
// int n;

// double dp()
// {
//     for (int i = 1; i <= n + 1; i++)
//         f[i][i - 1] = q[i - 1], w[i][i - 1] = q[i - 1];
//     for (int len = 1; len <= n; len++)
//         for (int i = 1; i + len - 1 <= n; i++)
//         {
//             int j = i + len - 1;
//             f[i][j] = 1e8;
//             w[i][j] = w[i][j - 1] + p[j] + q[j];
//             for (int k = i; k <= j; k++)
//             {
//                 double t = f[i][k - 1] + f[k + 1][j] + w[i][j];
//                 if (t < f[i][j])
//                     f[i][j] = t;
//             }
//         }
//     return f[1][n];
// }

// int main()
// {
//     cin >> n;
//     for (int i = 1; i <= n; i++)
//         cin >> p[i];
//     for (int i = 0; i <= n; i++)
//         cin >> q[i];
//     printf("%.8lf\n", dp());
//     system("pause");
//     return 0;
// }
