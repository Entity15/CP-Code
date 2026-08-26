#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    int arr[100];
    for(int i=0;i<n;i++) cin>>arr[i];
    int first=INT_MIN, second=INT_MIN;
    for(int i=0;i<n;i++){
        if(arr[i]>first){ second=first; first=arr[i]; }
        else if(arr[i]>second && arr[i]!=first) second=arr[i];
    }
    cout << "Second Largest = " << second;
    return 0;
}
