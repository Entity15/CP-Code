#include <bits/stdc++.h>
using namespace std;

int arraySum(int arr[],int n){
    if(n==0) return 0;
    return arr[n-1]+arraySum(arr,n-1);
}
int main(){
    int n; cin>>n;
    int arr[100];
    for(int i=0;i<n;i++) cin>>arr[i];
    cout << arraySum(arr,n);
    return 0;
}
