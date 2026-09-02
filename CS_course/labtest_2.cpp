#include <bits/stdc++.h>
using namespace std;

void bsearch(int x){
    int n; cin >> n;
    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1 - i; j++){
            if(a[j] > a[j+1]) swap(a[j], a[j+1]);
        }
    }
    bool found = false;
    int left, right, mid;
    left = 0; right = sizeof(a)/sizeof(a[0]); mid = left + right / 2;

    while(n--){
        if(a[left] == x || a[mid] == x || a[right] == x){
            found = true;
        }
        if(x < a[mid]){
            right = mid - 1;
            mid = left + right / 2;
        }
        else{
            left = mid + 1;
            mid = left + right / 2;
        }
    }
    (found) ? cout << 1 : cout << "invalid";
}

int main(){
    
    string s; cin >> s;
    stack<char> st;
    for(int i = 0; s[i] != '\0'; i++){
        st.push(s[i]);
    }
    cout << int(s[0]);

    bsearch(6);
    
}