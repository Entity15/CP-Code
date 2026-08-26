#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    int a[10][10];
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>a[i][j];
    bool symmetric=true;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(a[i][j]!=a[j][i]) symmetric=false;
    cout << (symmetric ? "Symmetric" : "Not Symmetric");
    return 0;
}
