#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    int arr[100];
    for(int i=0;i<n;i++) cin>>arr[i];
    int key; cin>>key;
    int lo=0, hi=n-1, pos=-1;
    while(lo<=hi){
        int mid=(lo+hi)/2;
        if(arr[mid]==key){ pos=mid; break; }
        else if(arr[mid]<key) lo=mid+1;
        else hi=mid-1;
    }
    cout << (pos!=-1 ? "Found at index " + to_string(pos) : "Not Found");
    return 0;
}
