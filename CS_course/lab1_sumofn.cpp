#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n, sum = 0; cin >> n;
    int i = 1;
    while (i <= n) {
        sum += i;
        i++;
    }
    cout << "Sum = " << sum;
    return 0;
    
}