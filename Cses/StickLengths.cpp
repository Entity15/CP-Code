#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll findAns(ll y, vector<ll> &a){
    ll ans = 0;
    for(auto e : a) ans += abs(e - y);
    return ans;
}

int main(){
    
    ll n; cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    ll lo = 1, hi = 1e9, mid1, mid2;

    while(hi - lo > 3){
        mid1 = lo + (hi - lo) / 3;
        mid2 = hi - (hi - lo) / 3;
        ll ans1 = findAns(mid1, a);
        ll ans2 = findAns(mid2, a);

        if(ans1 > ans2){
            lo = mid1;
        }else{
            hi = mid2;
        }
    }

    ll finalans = 1e18;
    for(ll y = lo; y <= hi; y++){
        finalans = min(finalans, findAns(y,a));
    }
    cout << finalans;
}