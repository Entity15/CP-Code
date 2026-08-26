#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        if (i % 7 == 0) {
            cout << "First divisible by 7 = " << i;
            break;
        }
    }
    return 0;
    
}