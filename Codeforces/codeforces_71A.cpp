#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        string x;
        cin >> x;

        (x.size() > 10) ? cout << x[0] << (int)x.size() - 2 << x[x.size() - 1] << endl : cout << x << endl;
    }
}