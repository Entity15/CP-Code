#include <bits/stdc++.h>
using namespace std;

int area(int side){ return side*side; }
int area(int l,int b){ return l*b; }
int main(){
    cout << "Square = " << area(4) << endl;
    cout << "Rectangle = " << area(3,5);
    return 0;
}
