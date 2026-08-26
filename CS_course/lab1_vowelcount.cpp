#include <bits/stdc++.h>
using namespace std;

int main(){
    
    string s; cin >> s;
    int count = 0;
    for (int i = 0; i < s.length(); i++) {
        char c = tolower(s[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') count++;
    }
    cout << "Vowel count = " << count;
    return 0;
    
}