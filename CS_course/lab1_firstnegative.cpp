#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n; cin >> n;
    int arr[100];
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            cout << "Stopped at negative number: " << arr[i];
            break;
        }
        cout << arr[i] << " ";
    }
    return 0;
    
}