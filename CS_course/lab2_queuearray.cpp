#include <bits/stdc++.h>
using namespace std;

int main(){
    int arr[100], front=0, rear=-1, n; cin>>n;
    for(int i=0;i<n;i++){
        rear++;
        arr[rear]=i+1;
    }
    while(front<=rear){
        cout << arr[front] << " ";
        front++;
    }
    return 0;
}
