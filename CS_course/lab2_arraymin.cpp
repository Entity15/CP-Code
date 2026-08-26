#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    int arr[100];
    for(int i=0;i<n;i++) cin>>arr[i];
    int mn=arr[0];
    for(int i=1;i<n;i++) if(arr[i]<mn) mn=arr[i];
    cout << "Min = " << mn;
    return 0;
}
