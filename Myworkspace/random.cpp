// 随机生成整数序列  n <= 10^5  x <= 10^9(int范围内)
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <random>

// using namespace std;
// int random(int n)
// {
//     return (long long)rand() * rand() % n;
// }
int main()
{
    // srand((unsigned)time(0));
    // freopen("data.in","w",stdout);
    // int m = random(100000) + 1;
    // for(int i = 0 ; i < m ; i ++)
    // {
    //     printf("%d %d\n",random(100000) + 1,random(100000) + 1);
    // }

    std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
    std::cout << rng() << '\n';

    system("pause");
}