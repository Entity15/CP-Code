#include <bits/stdc++.h>
using namespace std;

int main()
{

    long long n, x, total;
    cin >> n;
    long long a[n];

    for (long long i = 0; i < n; i++)
    {
        cin >> x;
        a[i] = x;
    }
    for (long long i = 1; i < n - 1; i++)
    {
        if (a[i] > a[i + 1])
        {
            a[i + 1]++;
            total++;
        }
    }

    cout << total << endl;
}