#include <bits/stdc++.h>
using namespace std;

void swapNums(int &a,int &b){
    int t=a; a=b; b=t;
}
int main(){
    int a,b; cin>>a>>b;
    swapNums(a,b);
    cout << "a = " << a << ", b = " << b;
    return 0;
}
