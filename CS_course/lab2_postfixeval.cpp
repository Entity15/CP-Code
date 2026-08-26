#include <bits/stdc++.h>
using namespace std;

int main(){
    string exp; cin>>exp;
    stack<int> st;
    for(char c: exp){
        if(isdigit(c)) st.push(c-'0');
        else{
            int b=st.top(); st.pop();
            int a=st.top(); st.pop();
            int res=0;
            if(c=='+') res=a+b;
            else if(c=='-') res=a-b;
            else if(c=='*') res=a*b;
            else if(c=='/') res=a/b;
            st.push(res);
        }
    }
    cout << "Result = " << st.top();
    return 0;
}
