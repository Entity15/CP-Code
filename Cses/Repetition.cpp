#include <bits/stdc++.h>
using namespace std;
 
int main(){
    
    string d;
    cin >> d;
 
    int best_run, current_run;
    best_run = current_run = 1;
 
    for(int i = 0; i < d.size() - 1; i++){
        if(d[i] == d[i + 1]){
            current_run++;
        }else{
            current_run = 1;
        }
        if(current_run > best_run){
            best_run = current_run;
        } 
    }
 
    cout << best_run;   
}