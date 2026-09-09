#include <bits/stdc++.h>
using namespace std;

// ============================================================
// 1. CAESAR CIPHER
// ============================================================
string caesarEncrypt(string text, int key) {
    string result = "";
    for (int i = 0; i < (int)text.size(); i++) {
        char c = text[i];
        if (c >= 'a' && c <= 'z') {
            c = 'a' + (c - 'a' + key) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            c = 'A' + (c - 'A' + key) % 26;
        }
        result += c;
    }
    return result;
}

string caesarDecrypt(string text, int key) {
    // decrypting is just encrypting with the opposite shift
    return caesarEncrypt(text, 26 - (key % 26));
}

// ============================================================
// 2. STREAM CIPHER (XOR with a repeating key)
// ============================================================
// Same function does both encrypt and decrypt, because XOR-ing
// twice with the same key gives you back the original.
string streamCipher(string text, string key) {
    string result = "";
    for (int i = 0; i < (int)text.size(); i++) {
        char keyChar = key[i % key.size()]; // repeat the key as needed
        result += (char)(text[i] ^ keyChar);
    }
    return result;
}

// ============================================================
// 3. ONE-TIME PAD (XOR with a pad the same length as the text)
// ============================================================
string onePad(string text, string pad) {
    string result = "";
    for (int i = 0; i < (int)text.size(); i++) {
        result += (char)(text[i] ^ pad[i]); // pad must be >= text length
    }
    return result;
}

string generateRandomPad(int length) {
    string pad = "";
    for (int i = 0; i < length; i++) {
        pad += (char)(rand() % 256);
    }
    return pad;
}

// ============================================================
// 4. AUTOKEY CIPHER
// ============================================================
// Same idea as Caesar, but instead of one fixed shift, each letter
// gets its own shift value that comes from the key. Once the key
// runs out, we keep going using the message itself as the key.
string autoKeyEncrypt(string text, string key) {
    string result = "";
    string fullKey = key + text; // key, then the message extends it

    for (int i = 0; i < (int)text.size(); i++) {
        char c = text[i];
        char k = toupper(fullKey[i]);
        int shift = k - 'A';

        if (c >= 'a' && c <= 'z') {
            c = 'a' + (c - 'a' + shift) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            c = 'A' + (c - 'A' + shift) % 26;
        }
        result += c;
    }
    return result;
}

string autoKeyDecrypt(string text, string key) {
    string result = "";
    string fullKey = key; // we build this up as we decrypt each letter

    for (int i = 0; i < (int)text.size(); i++) {
        char c = text[i];
        char k = toupper(fullKey[i]);
        int shift = k - 'A';
        char plain;

        if (c >= 'a' && c <= 'z') {
            plain = 'a' + ((c - 'a' - shift) % 26 + 26) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            plain = 'A' + ((c - 'A' - shift) % 26 + 26) % 26;
        } else {
            plain = c;
        }
        result += plain;
        fullKey += toupper(plain); // extend the key with the plaintext we just found
    }
    return result;
}

// ============================================================
// Helpers to show/enter "number list" text for Stream Cipher / OTP
// e.g. "104 101 108 108 111"
// ============================================================
string textToNumbers(string text) {
    string result = "";
    for (int i = 0; i < (int)text.size(); i++) {
        result += to_string((unsigned char)text[i]);
        if (i != (int)text.size() - 1) result += " ";
    }
    return result;
}

string numbersToText(string numbers) {
    string result = "";
    stringstream ss(numbers);
    int value;
    while (ss >> value) {
        result += (char)value;
    }
    return result;
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

    cout << "Enter key (any word): ";
    string key; getline(cin, key);

    if (mode == 1) {
        cout << "Enter plaintext: ";
        string text; getline(cin, text);
        string cipher = streamCipher(text, key);
        cout << "Ciphertext (numbers): " << textToNumbers(cipher) << "\n";
    } else {
        cout << "Enter ciphertext (numbers, space separated): ";
        string numbers; getline(cin, numbers);
        string cipherText = numbersToText(numbers);
        string plain = streamCipher(cipherText, key); // XOR again = decrypt
        cout << "Plaintext: " << plain << "\n";
    }
}

void runOTP() {
    cout << "1) Encrypt  2) Decrypt: ";
    int mode; cin >> mode; cin.ignore();

    if (mode == 1) {
        cout << "Enter plaintext: ";
        string text; getline(cin, text);

        cout << "1) Auto-generate a random pad  2) Type my own pad\n";
        int padChoice; cin >> padChoice; cin.ignore();

        string pad;
        if (padChoice == 1) {
            pad = generateRandomPad(text.size());
            cout << "Generated pad (numbers) - SAVE THIS to decrypt later:\n";
            cout << textToNumbers(pad) << "\n";
        } else {
            cout << "Enter pad text (same length as your message): ";
            getline(cin, pad);
        }

        string cipher = onePad(text, pad);
        cout << "Ciphertext (numbers): " << textToNumbers(cipher) << "\n";
    } else {
        cout << "Enter ciphertext (numbers, space separated): ";
        string numbers; getline(cin, numbers);
        string cipherText = numbersToText(numbers);

        cout << "Enter pad (numbers, space separated - same one used to encrypt): ";
        string padNumbers; getline(cin, padNumbers);
        string pad = numbersToText(padNumbers);

        string plain = onePad(cipherText, pad);
        cout << "Plaintext: " << plain << "\n";
    }
}

void runAutoKey() {
    cout << "1) Encrypt  2) Decrypt: ";
    int mode; cin >> mode; cin.ignore();

    cout << "Enter text: ";
    string text; getline(cin, text);

    cout << "Enter key (letters): ";
    string key; getline(cin, key);

    string result = (mode == 1) ? autoKeyEncrypt(text, key) : autoKeyDecrypt(text, key);
    cout << "Result: " << result << "\n";
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