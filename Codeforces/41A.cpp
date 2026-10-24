#include <bits/stdc++.h>
using namespace std;

int main(){

    string s1, s2;
    cin >> s1 >> s2;

    bool same = (s1.length() == s2.length());
    for(size_t i = 0; same && i < s1.length(); i++){
        if(s1[i] != s2[s1.length() - 1 - i]) same = false;
    }

    cout << (same ? "YES" : "NO") << endl;
}
