#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    queue<int> q;
    for(int i=0;i<n;i++){
        int x; cin>>x;
        q.push(x);
    }
    stack<int> st;
    int half=n/2;
    for(int i=0;i<half;i++){
        st.push(q.front());
        q.pop();
    }
    while(!st.empty()){
        q.push(st.top());
        st.pop();
    }
    for(int i=0;i<half;i++){
        q.push(q.front());
        q.pop();
    }
    for(int i=0;i<half;i++){
        st.push(q.front());
        q.pop();
    }
    while(!st.empty()){
        q.push(st.top());
        st.pop();
        q.push(q.front());
        q.pop();
    }
    while(!q.empty()){
        cout << q.front() << " ";
        q.pop();
    }
    return 0;
}
