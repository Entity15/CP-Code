#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    long long max, max2;
    max = max2 = 0;

    for (long long i = 0; i < s.length() - 1; i++)
    {
        if (s[i] == s[i + 1])
        {
            max2++;
        }
        else
        {
            max2 = 0;
        }

        if (max2 > max)
            max = max2;
    }
    if (max == 0)
        max = 1;
    cout << max << endl;
}