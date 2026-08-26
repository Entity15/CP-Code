#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n, sum = 0, x, y, max = 0; cin >> n;
    for(int i = 0; i < n; i++){
        cin >> x >> y;
        sum -= x;
        sum += y;
        if(sum > max) max = sum;
    }

    cout << max;
}