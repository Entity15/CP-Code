#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    int arr[100];
    for(int i=0;i<n;i++) cin>>arr[i];
    int key; cin>>key;
    int first=lower_bound(arr, arr+n, key) - arr;
    int last=upper_bound(arr, arr+n, key) - arr;
    cout << "Count = " << (last - first);
    return 0;
}
