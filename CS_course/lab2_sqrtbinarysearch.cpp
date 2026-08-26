#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    int lo=0, hi=n, ans=0;
    while(lo<=hi){
        long long mid=(lo+hi)/2;
        if(mid*mid<=n){ ans=mid; lo=mid+1; }
        else hi=mid-1;
    }
    cout << "Square Root = " << ans;
    return 0;
}
