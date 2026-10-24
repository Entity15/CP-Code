#include <bits/stdc++.h>
using namespace std;

int main(){

    int n; cin >> n;
    vector<long long> coins(n);
    for(auto &c : coins) cin >> c;

    sort(coins.begin(), coins.end());

    // every sum in [1, reach] can be formed so far
    long long reach = 0;
    for(auto c : coins){
        if(c > reach + 1) break;
        reach += c;
    }

    cout << reach + 1 << endl;
}
