#include <bits/stdc++.h>
#include <queue>

using namespace std;
priority_queue<int, vector<int>> heap;
int n, k, x;
int main()
{
    cin >> n >> k >> x;
    while (n--)
    {
        int c;
        cin >> c;
        heap.push(c);
    }
    while (k--)
    {
        int t = heap.top();
        heap.pop();
        t -= x;
        heap.push(t);
    }

    cout << heap.top() << '\n';
}