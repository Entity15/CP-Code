#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    int arr[100];
    for(int i=0;i<n;i++) cin>>arr[i];
    int lo=0, hi=n-1;
    while(lo<hi){
        int mid=(lo+hi)/2;
        if(arr[mid]>arr[mid+1]) hi=mid;
        else lo=mid+1;
    }
    cout << "Peak Element = " << arr[lo];
    return 0;
}
