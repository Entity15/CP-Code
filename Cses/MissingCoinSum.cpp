#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n; cin >> n;
    vector <int> max, sum;

    for(int i = 0; i < n; i++){
        int x; cin >> x;
        max.push_back(x);
    }

    sort(max.begin(), max.end());

    for(int i = 0; i < n; i++){
        sum[i] = i;
        for(auto a : max){
            sum[i + a] = i + a;
        }
        if(sum[i + 1] != i + 1){
            cout << i + 1 << endl;
            break;
        }
        if(sum[i - 1] != i - 1){
            cout << i - 1 << endl;
            break;
        }
    }
    
}
//farsi na