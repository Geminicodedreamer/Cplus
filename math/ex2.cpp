#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "../math/matplotlib-cpp-master/matplotlib-cpp-master/matplotlibcpp.h" // 包含matplotlib-cpp库

using namespace std;
namespace plt = matplotlibcpp;

vector<double> depths = {9.01, 8.96, 7.96, 7.96, 8.02, 9.05, 10.13, 11.18, 12.26, 13.28, 13.32, 12.61, 11.29, 10.22, 9.15, 7.95, 7.95, 8.86, 9.81, 10.80, 10.93};

struct Polynomial
{
    double a, b, c;
};

Polynomial polynomialFit(const vector<double> &depths)
{
    int n = depths.size();
    double sum_x = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0;
    double sum_y = 0, sum_xy = 0, sum_x2y = 0;
    double deltaX = 20.0 / (n - 1);

    for (int i = 0; i < n; ++i)
    {
        double x = i * deltaX;
        double y = depths[i];
        sum_x += x;
        sum_x2 += x * x;
        sum_x3 += x * x * x;
        sum_x4 += x * x * x * x;
        sum_y += y;
        sum_xy += x * y;
        sum_x2y += x * x * y;
    }

    double denom = n * (sum_x2 * sum_x4 - sum_x3 * sum_x3) - sum_x * (sum_x * sum_x4 - sum_x2 * sum_x3) + sum_x2 * (sum_x * sum_x3 - sum_x2 * sum_x2);

    double a = (n * (sum_x2 * sum_x2y - sum_x3 * sum_xy) - sum_x * (sum_x * sum_x2y - sum_x2 * sum_xy) + sum_x2 * (sum_x * sum_xy - sum_x2 * sum_y)) / denom;
    double b = (n * (sum_xy * sum_x4 - sum_x3 * sum_x2y) - sum_x * (sum_y * sum_x4 - sum_x2 * sum_x2y) + sum_x2 * (sum_y * sum_x3 - sum_x2 * sum_xy)) / denom;
    double c = (sum_x2 * (sum_x2 * sum_x2y - sum_x3 * sum_xy) - sum_x * (sum_x * sum_x2y - sum_x2 * sum_xy) + sum_y * (sum_x * sum_x3 - sum_x2 * sum_x2)) / denom;

    return {a, b, c};
}

void plotDataAndFit(const vector<double> &depths, const Polynomial &poly)
{
    vector<double> x_data, y_data, y_fit;
    double deltaX = 20.0 / (depths.size() - 1);

    for (int i = 0; i < depths.size(); ++i)
    {
        double x = i * deltaX;
        x_data.push_back(x);
        y_data.push_back(depths[i]);
    }

    for (double x = 0; x <= 20; x += 0.1)
    {
        double y = poly.a * x * x + poly.b * x + poly.c;
        y_fit.push_back(y);
    }

    plt::scatter(x_data, y_data, 10, {{"label", "Data"}});
    plt::plot(x_data, y_fit, {{"label", "Fit"}, {"color", "red"}});
    plt::xlabel("x");
    plt::ylabel("Depth");
    plt::legend();
    plt::save("plot.png");
}

int main()
{
    Polynomial coefficients = polynomialFit(depths);
    cout << "拟合曲线函数: y = " << coefficients.a << "x^2 + " << coefficients.b << "x + " << coefficients.c << endl;

    plotDataAndFit(depths, coefficients);

    return 0;
}
