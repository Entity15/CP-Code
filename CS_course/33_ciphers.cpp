#include <bits/stdc++.h>
using namespace std;

char shiftLetter(char c, int shift) {
    while (shift < 0) {
        shift = shift + 26;
    }
    while (shift >= 26) {
        shift = shift - 26;
    }

    if (c >= 'a' && c <= 'z') {
        int position = c - 'a';
        position = position + shift;
        if (position >= 26) {
            position = position - 26;
        }
        return 'a' + position;
    }

    if (c >= 'A' && c <= 'Z') {
        int position = c - 'A';
        position = position + shift;
        if (position >= 26) {
            position = position - 26;
        }
        return 'A' + position;
    }

    return c;
}

int letterToShift(char k) {
    if (k >= 'a' && k <= 'z') {
        return k - 'a';
    }
    if (k >= 'A' && k <= 'Z') {
        return k - 'A';
    }
    return 0;
}

// ============================================================
// 1. CAESAR CIPHER
// ============================================================

string caesarEncrypt(string text, int key) {
    string result = "";
    int n = text.size();
    for (int i = 0; i < int(n); i++) {
        result = result + shiftLetter(text[i], key);
    }
    return result;
}

string caesarDecrypt(string text, int key) {
    return caesarEncrypt(text, -key);
}

// ============================================================
// 2. STREAM CIPHER
// ============================================================

string streamCipherEncrypt(string text, string key) {
    string result = "";
    int keyIndex = 0;

    for (int i = 0; i < (int)text.size(); i++) {
        char keyChar = key[keyIndex];
        int shift = letterToShift(keyChar);
        result = result + shiftLetter(text[i], shift);

        keyIndex = keyIndex + 1;
        if (keyIndex >= (int)key.size()) {
            keyIndex = 0;
        }
    }
    return result;
}

string streamCipherDecrypt(string text, string key) {
    string result = "";
    int keyIndex = 0;

    for (int i = 0; i < (int)text.size(); i++) {
        char keyChar = key[keyIndex];
        int shift = letterToShift(keyChar);
        result = result + shiftLetter(text[i], -shift);

        keyIndex = keyIndex + 1;
        if (keyIndex >= (int)key.size()) {
            keyIndex = 0;
        }
    }
    return result;
}

// ============================================================
// 3. ONE-TIME PAD 
// ============================================================

string onePadEncrypt(string text, string pad) {
    string result = "";
    for (int i = 0; i < (int)text.size(); i++) {
        int shift = letterToShift(pad[i]);
        result = result + shiftLetter(text[i], shift);
    }
    return result;
}

string onePadDecrypt(string text, string pad) {
    string result = "";
    for (int i = 0; i < (int)text.size(); i++) {
        int shift = letterToShift(pad[i]);
        result = result + shiftLetter(text[i], -shift);
    }
    return result;
}

// ============================================================
// 4. AUTOKEY CIPHER
// ============================================================

string autoKeyEncrypt(string text, string key) {
    string result = "";
    string fullKey = key + text;

    for (int i = 0; i < (int)text.size(); i++) {
        int shift = letterToShift(fullKey[i]);
        result = result + shiftLetter(text[i], shift);
    }
    return result;
}

string autoKeyDecrypt(string text, string key) {
    string result = "";
    string fullKey = key;

    for (int i = 0; i < (int)text.size(); i++) {
        int shift = letterToShift(fullKey[i]);
        char plainChar = shiftLetter(text[i], -shift);
        result = result + plainChar;
        fullKey = fullKey + plainChar;
    }
    return result;
}

string convertKeyInputToLetters(string keyInput) {
    string key = "";
    int i = 0;

    while (i < (int)keyInput.size()) {
        char c = keyInput[i];

        if (c == ' ' || c == '\t') {
            i = i + 1;
            continue;
        }

        if (isdigit(c)) {
            string digits = "";
            while (i < (int)keyInput.size() && isdigit(keyInput[i])) {
                digits = digits + keyInput[i];
                i = i + 1;
            }

            int number = stoi(digits);
            while (number >= 26) {
                number = number - 26; // keep the number in range 0-25
            }

            char letter = 'A' + number;
            key = key + letter;

        } else if (isalpha(c)) {
            key = key + c;
            i = i + 1;

        } else {
            i = i + 1; // some other symbol - just skip it
        }
    }

    return key;
}

// ============================================================
// MENU
// ============================================================

void runCaesar() {
    cout << "Enter text: ";
    string text; getline(cin, text);

    cout << "Enter shift key (a number): ";
    int key; cin >> key; cin.ignore();

    string result;
    result = caesarEncrypt(text, key);
    cout << "Result: " << result << "\n";
    cout << "Do you want to decrypt? y for YES, n for No" << endl;
    char conf; cin >> conf;
    if(conf == 'y'){
        result = caesarDecrypt(result, key);
        cout << "Result: " << result << "\n";
    }
}

void runStream() {
    cout << "Enter key: ";
    string key; getline(cin, key);

    cout << "Enter text: ";
    string text; getline(cin, text);

    string result;
    result = streamCipherEncrypt(text, key);
    cout << "Result: " << result << "\n";
    cout << "Do you want to decrypt? y for YES, n for No" << endl;
    char conf; cin >> conf;
    if (conf == 'y') {
        result = streamCipherDecrypt(result, key);
    }
    
}

void runOTP() {
        cout << "Enter plaintext: ";
        string text; getline(cin, text);

        string pad;
        cout << "Enter key: ";
        getline(cin, pad);

        string cipher = onePadEncrypt(text, pad);
        cout << "Ciphertext: " << cipher << "\n";

        cout << "Do you want to decrypt? y for YES, n for No" << endl;
        char conf; cin >> conf;

        if (conf == 'y'){
        string plain = onePadDecrypt(cipher, pad);
        cout << "Plaintext: " << plain << "\n";
        }
}

void runAutoKey() {
    cout << "1) Encrypt  2) Decrypt: ";
    int mode; cin >> mode; cin.ignore();

    cout << "Enter text: ";
    string text; getline(cin, text);

    cout << "Enter key: ";
    string keyInput; getline(cin, keyInput);
    string key = convertKeyInputToLetters(keyInput);

    if (key == "") {
        cout << "Key must contain at least one letter or number.\n";
        return;
    }

    string result;
    result = autoKeyEncrypt(text, key);
    cout << "Result: " << result << "\n";
    cout << "Do you want to decrypt? y for YES, n for No" << endl;
        char conf; cin >> conf;
    if (conf == 'y') {
        result = autoKeyDecrypt(result, key);
        cout << "Result: " << result << "\n";
    }
   
}

int main() {
    srand(time(0));

    while (true) {
        cout << "\n--- Cipher Menu ---\n";
        cout << "1. Caesar Cipher\n";
        cout << "2. Stream Cipher\n";
        cout << "3. One-Time Pad\n";
        cout << "4. Autokey Cipher\n";
        cout << "0. Exit\n";
        cout << "Choose: ";

        int choice; cin >> choice; cin.ignore();

        if (choice == 1) runCaesar();
        else if (choice == 2) runStream();
        else if (choice == 3) runOTP();
        else if (choice == 4) runAutoKey();
        else if (choice == 0) break;
        else cout << "Invalid choice.\n";
    }

    cout << "Goodbye.\n";
    return 0;
}