#include <bits/stdc++.h>
using namespace std;

int main(){
    
    string s1, s2; cin >> s1 >> s2;
    transform(s1.begin(), s1.end(), s1.begin(), [](unsigned char c){
        return tolower(c);
    });
    transform(s2.begin(), s2.end(), s2.begin(), [](unsigned char c){
        return tolower(c);
    });
    int sum = 0;
    for(int i = 0; i < s1.length(); i++){
        sum += int(s1[i]);
        sum -= int(s2[i]);
    }
    (sum == 0) ? cout << 0 : ((sum > 0) ? cout << 1 : cout << -1);
}

// aslkjlkasdd
// asdlkjdajwi