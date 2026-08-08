#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, total = 0;
    cin >> n;
    while (n--)
    {
        int x, sum;
        vector<int> v;
        for (int i = 0; i < 3; i++)
        {
            cin >> x;
            v.push_back(x);
        }
        sum = accumulate(v.begin(), v.end(), 0);
        if (sum > 1)
            total++;
    }
    cout << total << endl;
}