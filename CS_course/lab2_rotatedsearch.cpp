#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    int arr[100];
    for(int i=0;i<n;i++) cin>>arr[i];
    int key; cin>>key;
    int lo=0, hi=n-1, result=-1;
    while(lo<=hi){
        int mid=(lo+hi)/2;
        if(arr[mid]==key){ result=mid; break; }
        if(arr[lo]<=arr[mid]){
            if(key>=arr[lo] && key<arr[mid]) hi=mid-1;
            else lo=mid+1;
        } else {
            if(key>arr[mid] && key<=arr[hi]) lo=mid+1;
            else hi=mid-1;
        }
    }
    cout << (result!=-1 ? "Found at index " + to_string(result) : "Not Found");
    return 0;
}
