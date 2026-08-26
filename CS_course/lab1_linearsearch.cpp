#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n; cin >> n;
    int arr[100];
    for (int i = 0; i < n; i++) cin >> arr[i];
    int key; cin >> key;
    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) { pos = i; break; }
    }
    if (pos != -1) cout << "Found at index " << pos;
    else cout << "Not Found";
    return 0;
    
}