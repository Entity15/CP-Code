#include <bits/stdc++.h>
using namespace std;

long long power(int x,int n){
    long long result=1;
    for(int i=0;i<n;i++) result*=x;
    return result;
}
int main(){
    int x,n; cin>>x>>n;
    cout << power(x,n);
    return 0;
}
