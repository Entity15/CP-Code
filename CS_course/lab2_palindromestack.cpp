#include <bits/stdc++.h>
using namespace std;

int main(){
    string s; cin>>s;
    stack<char> st;
    for(char c: s) st.push(c);
    string rev="";
    while(!st.empty()){
        rev+=st.top();
        st.pop();
    }
    cout << (s==rev ? "Palindrome" : "Not Palindrome");
    return 0;
}
