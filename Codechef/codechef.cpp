#include <bits/stdc++.h>
using namespace std;

int main()
{

    int f1, p1, f2, p2;
    cin >> f1 >> p1 >> f2 >> p2;

    if (abs(f1 - p1) == abs(f2 - p2))
        cout << "Both" << endl;
    else
        (abs(f1 - p1) < abs(f2 - p2)) ? cout << "First" << endl : cout << "Second" << endl;
}