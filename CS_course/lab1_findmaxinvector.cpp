#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    int maxVal = v[0];
    for (int i = 1; i < v.size(); i++)
        if (v[i] > maxVal) maxVal = v[i];
    cout << "Max = " << maxVal << ", Size = " << v.size();
    return 0;
    
}

//maxVal =*max_element(v.begin(), v.end());