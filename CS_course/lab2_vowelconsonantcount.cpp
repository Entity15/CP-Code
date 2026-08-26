#include <bits/stdc++.h>
using namespace std;

int main(){
    string s; cin>>s;
    int vowels=0, consonants=0;
    for(char c: s){
        c=tolower(c);
        if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u') vowels++;
        else if(isalpha(c)) consonants++;
    }
    cout << "Vowels = " << vowels << ", Consonants = " << consonants;
    return 0;
}
