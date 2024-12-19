#include <bits/stdc++.h>

using namespace std;
class Retangular
{
public:
    int x, y;
    Retangular(int x, int y)
    {
        this->x = x, this->y = y;
    }

    void tell()

    {
        cout << "This is a retangular which covers " << x * y << " m^2";
    }
};

class Box
{
public:
    int x, y, h;
    Box(int x, int y, int h)
    {
        this->x = x, this->y = y, this->h = h;
    }

    void tell()
    {
        cout << "This is a Box which covers " << x * y * h << " m^3";
    }
};

int q[10010], idx;

int main()
{
    int x;
    while (cin >> x)
    {
        q[idx++] = x;
    }

    if (idx == 1)
    {
        cout << "Nothing" << '\n';
    }
    else if (idx == 2)
    {
        Retangular a = Retangular(q[0], q[1]);
        a.tell();
    }
    else
    {
        Box a = Box(q[0], q[1], q[2]);
        a.tell();
    }

    system("pause");
    return 0;
}