#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int dst, moves = 0; cin >> dst;
    for(int i = 5; i > 0; i--){
        while(dst > 0){
            dst -= i;
            moves++;
        }
    }
    cout << moves << endl;
}