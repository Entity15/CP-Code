#include <bits/stdc++.h>
using namespace std;

bool isEven(int n) { return n % 2 == 0; }

int main() {

    int n; cin >> n;
    cout << (isEven(n) ? "Even" : "Odd");
    return 0;
    
}