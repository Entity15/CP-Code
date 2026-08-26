#include <bits/stdc++.h>
using namespace std;

int main(){
    string s; char ch; cin>>s>>ch;
    int count=0;
    for(char c: s) if(c==ch) count++;
    cout << "Occurrences = " << count;
    return 0;
}
