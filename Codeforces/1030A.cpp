#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n; cin >> n;
    int a[n];
    bool easy = true;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] == 1) easy = false;
    }

    (easy) ? cout << "EASY" : cout << "HARD";
    
}