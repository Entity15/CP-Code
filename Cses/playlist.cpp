#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n; cin >> n;
    int a[n];
    for(int i = 0; i < n; i++) cin >> a[i];

    int l = 0, r = 0;
    set<int> st;
    int ans = 0;

    while(r < n){
        if(st.find(a[r]) != st.end()){
            while(a[l] != a[r]){
                st.erase(a[l]);
                ++l;
            }
            ++l; ++r;
            continue;
        }

        st.insert(a[r]);
        ans = max(ans, r - l + 1);
        ++r;
    }

    cout << ans << endl;
    
}