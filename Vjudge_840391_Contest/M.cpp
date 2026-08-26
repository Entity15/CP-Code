#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int t; cin >> t;
    while(t--){
        int n, k, x; cin >> n >> k;
        vector<int> h,p;
        for(int i = 0; i < n; i++){
            cin >> x;
            h.push_back(x);
        }
        for(int i = 0; i < n; i++){
            cin >> x;
            p.push_back(x);
        }
        int health = accumulate(h.begin(), h.end(), 0);
        while(health > 0 && k > 0){
            for(int i = 0; i < n; i++){
                h[i] - k;
            }
            
            health = accumulate(h.begin(), h.end(), 0);
            
        }
    }
    
}