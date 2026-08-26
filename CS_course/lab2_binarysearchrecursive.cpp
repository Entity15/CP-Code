#include <bits/stdc++.h>
using namespace std;

int binarySearch(int arr[], int lo, int hi, int key){
    if(lo>hi) return -1;
    int mid=(lo+hi)/2;
    if(arr[mid]==key) return mid;
    else if(arr[mid]<key) return binarySearch(arr,mid+1,hi,key);
    else return binarySearch(arr,lo,mid-1,key);
}
int main(){
    int n; cin>>n;
    int arr[100];
    for(int i=0;i<n;i++) cin>>arr[i];
    int key; cin>>key;
    int pos=binarySearch(arr,0,n-1,key);
    cout << (pos!=-1 ? "Found at index " + to_string(pos) : "Not Found");
    return 0;
}
