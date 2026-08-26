#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;i++) cin>>v[i];
    int idx; cin>>idx;
    v.erase(v.begin()+idx);
    for(int x: v) cout<<x<<" ";
    return 0;
}
