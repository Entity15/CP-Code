#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++) cin>>arr[i];
    vector<int> result(n,-1);
    stack<int> st;
    for(int i=n-1;i>=0;i--){
        while(!st.empty() && st.top()<=arr[i]) st.pop();
        if(!st.empty()) result[i]=st.top();
        st.push(arr[i]);
    }
    for(int x: result) cout<<x<<" ";
    return 0;
}
