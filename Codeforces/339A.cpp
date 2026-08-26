#include <bits/stdc++.h>
using namespace std;

int main(){
    
    string s; cin >> s;
    vector<int> n;
    for(int i = 0; i < s.length(); i+= 2){
        if(s[i] == '+') continue;
        n.push_back(int(s[i]));
    }
    sort(n.begin(), n.end());
    char c;
    for(int i = 0; i < n.size(); i++){
        c = n[i];
        if(i == (n.size() - 1)){
            cout << c;
            break;
        }
        cout << c << '+';
    }
    
}