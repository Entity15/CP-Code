#include <bits/stdc++.h>
using namespace std;

int main(){
    int r,c; cin>>r>>c;
    int a[10][10];
    for(int i=0;i<r;i++) for(int j=0;j<c;j++) cin>>a[i][j];
    int mx=a[0][0];
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            if(a[i][j]>mx) mx=a[i][j];
    cout << "Max = " << mx;
    return 0;
}
