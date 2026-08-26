#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int year;
    cin >> year;
    if (year % 4 == 0)
        cout << year << " is a Leap Year";
    else
        cout << year << " is not a Leap Year";
    return 0;
    
}