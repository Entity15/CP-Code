#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n; cin >> n;
    int a[n];

    for(int i = 0; i < n; i++) cin >> a[i];
    
    multiset<int> st;
    for(auto e : a){
        auto it = st.upper_bound(e);
        if(it != st.end()){
            st.erase(it);
        }
        st.insert(e);
    }

    cout << st.size() << endl;

}