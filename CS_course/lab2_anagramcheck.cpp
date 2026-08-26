#include <bits/stdc++.h>
using namespace std;

int main(){
    string a,b; cin>>a>>b;
    string x=a,y=b;
    sort(x.begin(),x.end());
    sort(y.begin(),y.end());
    cout << (x==y ? "Anagrams" : "Not Anagrams");
    return 0;
}
