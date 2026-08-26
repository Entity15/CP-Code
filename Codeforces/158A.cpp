#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n, x, cnt = 0; cin >> n >> x;
    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        if(a[i] == 0) continue;
        if(a[i] >= a[x-1]) cnt++;
    }
    cout << cnt << endl;
    
}