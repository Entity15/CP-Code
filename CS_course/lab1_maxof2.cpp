#include <bits/stdc++.h>
using namespace std;

int getMax(int a, int b) { return (a > b) ? a : b; }

int main() {

    int a, b; cin >> a >> b;
    cout << "Max = " << getMax(a, b);
    return 0;
    
}