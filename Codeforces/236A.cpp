#include <bits/stdc++.h>
using namespace std;

int main(){
    
    string s; cin >> s;
    int cnt = 0;
    for(int i = 0; i < s.length(); i++){
        for(int j = i; j < s.length(); j++){
            if(i == j || s[j] == '0') continue;
            if(s[i] == s[j]) s[j] = '0';
        }
    }
    for(int i = 0; i < s.length(); i++) if(s[i] == '0') cnt++;

    ((s.length() - cnt) % 2 == 0) ? cout << "CHAT WITH HER!" : cout << "IGNORE HIM!";
    
}