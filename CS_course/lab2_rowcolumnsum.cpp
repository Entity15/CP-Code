#include <bits/stdc++.h>
using namespace std;

int main(){
    int r,c; cin>>r>>c;
    int a[10][10];
    for(int i=0;i<r;i++) for(int j=0;j<c;j++) cin>>a[i][j];
    for(int i=0;i<r;i++){
        int rowSum=0;
        for(int j=0;j<c;j++) rowSum+=a[i][j];
        cout << "Row " << i << " Sum = " << rowSum << endl;
    }
    for(int j=0;j<c;j++){
        int colSum=0;
        for(int i=0;i<r;i++) colSum+=a[i][j];
        cout << "Column " << j << " Sum = " << colSum << endl;
    }
    return 0;
}
