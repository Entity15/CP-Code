#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int cntA = 0, cntD = 0, n;
    cin >> n;
    char c[n];
    for(int i = 0; i < n; i++){
        cin >> c[i];
        if(c[i] == 'A') cntA++;
        if(c[i] == 'D') cntD++;
    }
    (cntA == cntD) ? (cout << "Friendship") : ((cntA > cntD) ? cout << "Anton" : cout << "Danik");

    
}