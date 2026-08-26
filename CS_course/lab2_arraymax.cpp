#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    int arr[100];
    for(int i=0;i<n;i++) cin>>arr[i];
    int mx=arr[0];
    for(int i=1;i<n;i++) if(arr[i]>mx) mx=arr[i];
    cout << "Max = " << mx;
    return 0;
}
