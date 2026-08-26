#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    queue<string> q;
    q.push("1");
    for(int i=0;i<n;i++){
        string curr=q.front();
        q.pop();
        cout << curr << " ";
        q.push(curr+"0");
        q.push(curr+"1");
    }
    return 0;
}
