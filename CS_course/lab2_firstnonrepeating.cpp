#include <bits/stdc++.h>
using namespace std;

int main(){
    string s; cin>>s;
    map<char,int> freq;
    queue<char> q;
    for(char c: s){
        freq[c]++;
        q.push(c);
        while(!q.empty() && freq[q.front()]>1) q.pop();
    }
    if(!q.empty()) cout << "First non-repeating: " << q.front();
    else cout << "None";
    return 0;
}
