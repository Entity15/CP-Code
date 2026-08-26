#include <bits/stdc++.h>
using namespace std;

int main(){
    
    string s1, s2;
    cin >> s1 >> s2;
    bool same = true;
    int n;
    (s1.length() > s2.length()) ? n = s1.length() : n = s2.length();
    
    for(int i = 0, j = n - 1; i < n; i++, j--){
        if(s1[i] != s2[j]){
            same = false;
            break;
        }
    }
    (same) ? cout << "YES" : cout << "NO";
    
}