#include <bits/stdc++.h>
using namespace std;

int main(){
    int r,c; cin>>r>>c;
    int a[10][10];
    for(int i=0;i<r;i++) for(int j=0;j<c;j++) cin>>a[i][j];
    int top=0, bottom=r-1, left=0, right=c-1;
    while(top<=bottom && left<=right){
        for(int j=left;j<=right;j++) cout<<a[top][j]<<" ";
        top++;
        for(int i=top;i<=bottom;i++) cout<<a[i][right]<<" ";
        right--;
        if(top<=bottom){
            for(int j=right;j>=left;j--) cout<<a[bottom][j]<<" ";
            bottom--;
        }
        if(left<=right){
            for(int i=bottom;i>=top;i--) cout<<a[i][left]<<" ";
            left++;
        }
    }
    return 0;
}
