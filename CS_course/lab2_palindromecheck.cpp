#include <bits/stdc++.h>
using namespace std;

int main(){
    string s; cin>>s;
    string rev=s;
    reverse(rev.begin(), rev.end());
    cout << (s==rev ? "Palindrome" : "Not Palindrome");
    return 0;
}
