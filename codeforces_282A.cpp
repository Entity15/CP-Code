#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, total = 0;
    cin >> n;
    while (n--)
    {
        string s;
        cin >> s;

        if (s == "X++" || s == "++X")
            total++;
        if (s == "X--" || s == "--X")
            total--;
    }
    cout << total << endl;
}