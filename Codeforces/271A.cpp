#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n, x = 0, a[4]; cin >> n;
    int dn = n;
    bool distinct = true;
    for(int i = 0; i < 4; i++){
        a[i] = dn % 10;
        dn /= 10;
    }
}