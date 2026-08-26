#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int cnt = 0;
    string n; cin >> n;
    for(int i = 0; i < n.length(); i++){
        if(n[i] == '4' || n[i] == '7') cnt++;
    }
    (cnt == 4 || cnt == 7) ? cout << "YES" : cout << "NO";

    
}