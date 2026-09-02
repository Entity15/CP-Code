#include <bits/stdc++.h>
using namespace std;

int main() {

    string t;
    int shift;

    cin >> t >> shift;

    string encrypt = "";

    // Encryption
    for (int i = 0; i < t.length(); i++) {
        encrypt += (t[i] - 'A' + shift) % 26 + 'A';
    }

    cout << "Encrypted text: " << encrypt << endl;

    string decrypt = "";

    // Decryption
    for (int i = 0; i < encrypt.length(); i++) {
        decrypt += (encrypt[i] - 'A' - shift + 26) % 26 + 'A';
    }

    cout << "Decrypted text: " << decrypt << endl;

    return 0;
}