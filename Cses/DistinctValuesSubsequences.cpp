#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    
    ll n, x;
    cin >> n >> x;
    ll a[n];
    for(int i=0;i<n;i++) cin >> a[i];

    ll sum = 0, ans = 0;
    map<ll,ll> mp;
    mp[0]=1;

    for(int i=0;i<n;i++){
        sum += a[i];
        ll need = sum - x;
        ans += mp[need];
        mp[sum]++;
    }

    cout << ans << endl;
    
}