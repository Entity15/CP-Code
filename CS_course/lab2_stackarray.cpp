#include <bits/stdc++.h>
using namespace std;

int main(){
    int arr[100], top=-1, n; cin>>n;
    for(int i=0;i<n;i++){
        top++;
        arr[top]=i+1;
    }
    while(top>=0){
        cout << arr[top] << " ";
        top--;
    }
    return 0;
}
