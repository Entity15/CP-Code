#include <bits/stdc++.h>
using namespace std;

int main()
{

    int t;
    cin >> t;
    while (t--)
    {
        int n, k, x;
        cin >> n >> k;
        vector<int> v(n);
        for (int i = 0; i < n; i++)
        {
            cin >> x;
            v.push_back(x);
        }

        if (!(is_sorted(v.begin(), v.end())) && k > 1)
        {
            cout << "YES" << endl;
        }
        else if (is_sorted(v.begin(), v.end()))
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}