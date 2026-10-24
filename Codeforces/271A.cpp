#include <bits/stdc++.h>
using namespace std;

int main(){

    int n; cin >> n;

    for(int y = n + 1; ; y++){
        string s = to_string(y);
        set<char> digits(s.begin(), s.end());
        if(digits.size() == s.size()){
            cout << y << endl;
            return 0;
        }
    }
}
