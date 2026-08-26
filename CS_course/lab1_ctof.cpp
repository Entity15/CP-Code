#include <bits/stdc++.h>
using namespace std;

double toFahrenheit(double c) {
    return (c * 9.0 / 5.0) + 32;
}

int main() {

    double c; cin >> c;
    cout << "Fahrenheit = " << toFahrenheit(c);
    return 0;
    
}