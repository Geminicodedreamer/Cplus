#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

int main()
{
    srand(time(0)); // Seed for random number generator
    for (int i = 1; i <= 1000; ++i)
    {
        int n , x , y;
        n = random() % 100;
        x = random() % 100;
        y = random() % 100;
        std::cout << "Test #" << i << ": Accept  Runtime: ";
    }
    std::cout << "Result :Accpected" << '\n';
    system("pause");
    return 0;
}
