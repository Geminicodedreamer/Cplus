#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstdio>

#define MOD 998244353

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

ll mod_pow(ll base, ll exp, ll mod)
{
    ll result = 1;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// 生成测试用例
vector<pii> generate_test_case(int n, int m)
{
    set<pii> edges_set;
    while (edges_set.size() < m)
    {
        int u = rand() % n + 1;
        int v = rand() % n + 1;
        if (u != v)
        {
            edges_set.insert({min(u, v), max(u, v)});
        }
    }
    return vector<pii>(edges_set.begin(), edges_set.end());
}

int main()
{
    srand(time(0));

    int num_tests = 10000; // 生成10个测试用例

    for (int t = 0; t < num_tests; ++t)
    {
        int n = rand() % 100 + 1;                           // 顶点数 1-100000
        int m = min(n * (n - 1) / 2, rand() % 1000000 + 1); // 边数 1-1000000
        int k = rand() % (MOD - 1) + 1;                     // 颜色数 1-(MOD-1)

        vector<pii> edges = generate_test_case(n, m);

        // 写入到输入文件
        ofstream input_file("input.txt");
        input_file << n << " " << m << " " << k << endl;
        for (auto &edge : edges)
        {
            input_file << edge.first << " " << edge.second << endl;
        }
        input_file.close();

        // 运行 A.cpp (你的代码)
        system("g++ A.cpp -o A.exe && A.exe < input.txt > output_A.txt");

        // 运行 B.cpp (正确答案代码)
        system("g++ B.cpp -o B.exe && B.exe < input.txt > output_B.txt");

        // 读取输出文件
        ifstream output_A("output_A.txt");
        ifstream output_B("output_B.txt");

        ll result_A, result_B;
        output_A >> result_A;
        output_B >> result_B;

        output_A.close();
        output_B.close();

        // 比较结果
        if (result_A != result_B)
        {
            cout << "Test case " << t + 1 << " failed!" << endl;
            cout << "Input:" << endl;
            cout << n << " " << m << " " << k << endl;
            for (auto &edge : edges)
            {
                cout << edge.first << " " << edge.second << endl;
            }
            cout << "Output A: " << result_A << endl;
            cout << "Output B: " << result_B << endl;
            system("pause");
            return 0;
        }
        else
        {
            cout << "Test case " << t + 1 << " passed!" << endl;
        }
    }

    cout << "All test cases passed!" << endl;

    system("pause");
    return 0;
}
