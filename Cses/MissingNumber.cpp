#include <bits/stdc++.h>
using namespace std;
 
int main()
{
 
    int x;
    long long n;
    cin >> n;
 
    vector<int> v(n);
    vector<int> v1(n - 1);
 
    for (int i = 0; i < n; i++)
    {
        v.push_back(i + 1);
    }
    for (int i = 0; i < n - 1; i++)
    {
        cin >> x;
        v1.push_back(x);
    }
 
    cout << accumulate(v.begin(), v.end(), 0) - accumulate(v1.begin(), v1.end(), 0) << endl;
}