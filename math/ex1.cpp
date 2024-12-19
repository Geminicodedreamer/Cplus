#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// 深度数据
vector<double> depths = {9.01, 8.96, 7.96, 7.96, 8.02, 9.05, 10.13, 11.18, 12.26, 13.28, 13.32, 12.61, 11.29, 10.22, 9.15, 7.95, 7.95, 8.86, 9.81, 10.80, 10.93};

double calculateCableLength(const vector<double> &depths, double width)
{
    double totalLength = 0.0;
    double deltaX = width / (depths.size() - 1);

    for (size_t i = 1; i < depths.size(); ++i)
    {
        double deltaH = depths[i] - depths[i - 1];
        totalLength += sqrt(deltaX * deltaX + deltaH * deltaH);
    }

    return totalLength;
}

int main()
{
    double width = 20.0; // 河沟宽度
    double cableLength = calculateCableLength(depths, width);

    cout << "通过河沟所需光缆长度的近似值: " << cableLength << " 米" << endl;

    system("pause");
    return 0;
}
