#include <bits/stdc++.h>
using namespace std;

int main(){
    
    string s; cin >> s;
    string rev = s;
    for (int i = 0; i < s.length(); i++)
        rev[i] = s[s.length() - 1 - i];
    cout << ((s == rev) ? "Palindrome" : "Not Palindrome");
    return 0;
    
}