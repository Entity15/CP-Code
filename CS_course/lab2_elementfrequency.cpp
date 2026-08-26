#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    int arr[100];
    for(int i=0;i<n;i++) cin>>arr[i];
    map<int,int> freq;
    for(int i=0;i<n;i++) freq[arr[i]]++;
    for(auto p: freq) cout << p.first << " -> " << p.second << endl;
    return 0;
}
