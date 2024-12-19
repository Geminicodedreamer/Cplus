#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t = 0;
    while (1)
    {
        cout << "test " << ++t << endl;
        system("data.exe>data.in");
        system("D_In_Love.exe<data.in>data.out");
        system("G_1_Dances_Easy_version.exe<data.in>data.ans");
        if (system("fc data.out data.ans > diff.log"))
        {
            cout << "WA" << '\n';
            break;
        }
        cout << "AC" << '\n';
    }
}