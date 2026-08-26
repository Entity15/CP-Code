#include <bits/stdc++.h>
using namespace std;

int main(){
    int size; cin>>size;
    vector<int> cq(size,-1);
    int front=-1, rear=-1;
    int n; cin>>n;
    for(int i=0;i<n && i<size;i++){
        int x; cin>>x;
        if(front==-1) front=0;
        rear=(rear+1)%size;
        cq[rear]=x;
    }
    int i=front;
    while(true){
        cout << cq[i] << " ";
        if(i==rear) break;
        i=(i+1)%size;
    }
    return 0;
}
