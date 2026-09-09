#include <bits/stdc++.h>
using namespace std;

char shiftLetter(char c, int shift) {
    if (c >= 'a' && c <= 'z') {
        return 'a' + ((c - 'a' + shift) % 26 + 26) % 26;
    } else if (c >= 'A' && c <= 'Z') {
        return 'A' + ((c - 'A' + shift) % 26 + 26) % 26;
    }
    return c;
}

int letterToShift(char k) {
    if (k >= 'a' && k <= 'z') return k - 'a';
    if (k >= 'A' && k <= 'Z') return k - 'A';
    return 0;
}

// ============================================================
// 1. CAESAR CIPHER
// ============================================================

string caesarEncrypt(string text, int key) {
    string result = "";
    int n = text.size();
    for (int i = 0; i < int(n); i++) {
        result += shiftLetter(text[i], key);
    }
    return result;
}

string caesarDecrypt(string text, int key) {
    return caesarEncrypt(text, 26 - (key % 26));
}

// ============================================================
// 2. STREAM CIPHER
// ============================================================

string streamCipherEncrypt(string text, string key) {
    string result = "";
    for (int i = 0; i < (int)text.size(); i++) {
        char keyChar = key[i % key.size()]; // repeat the key as needed
        int shift = letterToShift(keyChar);
        result += shiftLetter(text[i], shift);
    }
    return result;
}

string streamCipherDecrypt(string text, string key) {
    string result = "";
    for (int i = 0; i < (int)text.size(); i++) {
        char keyChar = key[i % key.size()];
        int shift = letterToShift(keyChar);
        result += shiftLetter(text[i], -shift);
    }
    return result;
}

// ============================================================
// 3. ONE-TIME PAD
// ============================================================

string onePadEncrypt(string text, string pad) {
    string result = "";
    for (int i = 0; i < (int)text.size(); i++) {
        int shift = letterToShift(pad[i]); // pad must be >= text length
        result += shiftLetter(text[i], shift);
    }
    return result;
}

string onePadDecrypt(string text, string pad) {
    string result = "";
    for (int i = 0; i < (int)text.size(); i++) {
        int shift = letterToShift(pad[i]);
        result += shiftLetter(text[i], -shift);
    }
    return result;
}

// ============================================================
// 4. AUTOKEY CIPHER
// ============================================================

string autoKeyEncrypt(string text, vector<int> keyShifts) {
    string result = "";
    vector<int> fullShifts = keyShifts;
    for (char c : text) fullShifts.push_back(letterToShift(c));

    for (int i = 0; i < (int)text.size(); i++) {
        result += shiftLetter(text[i], fullShifts[i]);
    }
    return result;
}

string autoKeyDecrypt(string text, vector<int> keyShifts) {
    string result = "";
    vector<int> fullShifts = keyShifts;

    for (int i = 0; i < (int)text.size(); i++) {
        int shift = fullShifts[i];
        char plain = shiftLetter(text[i], -shift);
        result += plain;
        fullShifts.push_back(letterToShift(plain));
    }
    return result;
}

vector<int> parseKeyToShifts(const string &keyInput) {
    vector<int> shifts;
    bool hasSpace = keyInput.find_first_of(" \t") != string::npos;

    if (hasSpace) {
        stringstream ss(keyInput);
        string token;
        while (ss >> token) {
            bool isNumber = !token.empty();
            for (size_t j = 0; j < token.size(); j++) {
                char c = token[j];
                if (!isdigit((unsigned char)c) && !(c == '-' && j == 0)) { isNumber = false; break; }
            }
            if (isNumber && token != "-") {
                int num = stoi(token);
                shifts.push_back(((num % 26) + 26) % 26);
            } else {
                for (char c : token) {
                    if (isalpha((unsigned char)c)) shifts.push_back(letterToShift(c));
                }
            }
        }
    } else {
        for (char c : keyInput) {
            if (isdigit((unsigned char)c)) shifts.push_back(c - '0');
            else if (isalpha((unsigned char)c)) shifts.push_back(letterToShift(c));
        }
    }
    return shifts;
}

// ============================================================
// MENU
// ============================================================

void runCaesar() {
    cout << "1) Encrypt  2) Decrypt: ";
    int mode; cin >> mode; cin.ignore();

    cout << "Enter text: ";
    string text; getline(cin, text);

    cout << "Enter shift key (a number): ";
    int key; cin >> key; cin.ignore();

    string result = (mode == 1) ? caesarEncrypt(text, key) : caesarDecrypt(text, key);
    cout << "Result: " << result << "\n";
}

void runStream() {
    cout << "1) Encrypt  2) Decrypt: ";
    int mode; cin >> mode; cin.ignore();

    cout << "Enter key (letters only, any length): ";
    string key; getline(cin, key);

    cout << "Enter text: ";
    string text; getline(cin, text);

    string result = (mode == 1) ? streamCipherEncrypt(text, key) : streamCipherDecrypt(text, key);
    cout << "Result: " << result << "\n";
}

void runOTP() {
    cout << "1) Encrypt  2) Decrypt: ";
    int mode; cin >> mode; cin.ignore();

    if (mode == 1) {
        cout << "Enter plaintext: ";
        string text; getline(cin, text);

        string pad;
        
        cout << "Enter key (letters, same length as your message): ";
        getline(cin, pad);
        

        string cipher = onePadEncrypt(text, pad);
        cout << "Ciphertext: " << cipher << "\n";
    } else {
        cout << "Enter ciphertext: ";
        string text; getline(cin, text);

        cout << "Enter key: ";
        string pad; getline(cin, pad);

        string plain = onePadDecrypt(text, pad);
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
    vector<int> keyShifts = parseKeyToShifts(keyInput);

    if (keyShifts.empty()) {
        cout << "Key must contain at least one letter or number.\n";
        return;
    }

    string result = (mode == 1) ? autoKeyEncrypt(text, keyShifts) : autoKeyDecrypt(text, keyShifts);
    cout << "Result: " << result << "\n";
}

int main() {

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