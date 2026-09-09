#include <bits/stdc++.h>
using namespace std;
 
int main(){
    
    long long int count = 0, n, x;
    cin >> n;
    long long int a[n];
    for(int i = 0; i < n; i++){
        cin >> x;
        a[i] = x;
    }
    for(int i = 0; i < n - 1; i++){
        while(a[i] > a[i + 1]){
            a[i + 1]++;
            count++;
        }
    }
    cout << count;   
}