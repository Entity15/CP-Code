#include <bits/stdc++.h>
using namespace std;

int main(){
    
    string str; cin >> str;
    int b = 0, s = 0; char c;
    for(int i = 0; i < str.length(); i++){
        c = str[i];
        (c <= 90) ? b++ : s++;
    }
    (b == s) ? (transform(str.begin(), str.end(), str.begin(), ::tolower)) : ((b > s) ? (transform(str.begin(), str.end(), str.begin(), ::toupper)) : transform(str.begin(), str.end(), str.begin(), ::tolower));

    cout << str;
    
}