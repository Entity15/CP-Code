#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    int a[10][10];
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>a[i][j];
    bool identity=true;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            if(i==j && a[i][j]!=1) identity=false;
            if(i!=j && a[i][j]!=0) identity=false;
        }
    cout << (identity ? "Identity Matrix" : "Not Identity Matrix");
    return 0;
}
