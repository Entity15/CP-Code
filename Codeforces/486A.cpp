#include <bits/stdc++.h>
using namespace std;

int main(){
    
    long long int n; cin >> n;
    if(n % 2 == 0){
        n /= 2;
    }
    else{
        n = (n / 2) - n;
    }

    cout << n;
    
}