#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);

        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        int operations = 0;
        int prev = a[0];

        for (int i = 1; i < n; i++)
        {
            int curr = a[i];
            if (curr < prev)
            {
                int diff = prev - curr;
                int count = 0;

                while (curr < prev)
                {
                    curr *= 2;
                    count++;
                }

                operations = max(operations, count);
            }
            prev = max(prev, curr);
        }

        cout << operations << endl;
    }

    return 0;
}
