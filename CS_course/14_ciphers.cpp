#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Small helper: shift a single letter by `shift` positions,
// wrapping around a-z / A-Z. Works for encrypt (positive shift)
// and decrypt (call with shift = -shift). Non-letters pass
// through unchanged.
// ============================================================
char shiftLetter(char c, int shift) {
    if (c >= 'a' && c <= 'z') {
        return 'a' + ((c - 'a' + shift) % 26 + 26) % 26;
    } else if (c >= 'A' && c <= 'Z') {
        return 'A' + ((c - 'A' + shift) % 26 + 26) % 26;
    }
    return c; // spaces, punctuation, digits, etc. pass through untouched
}

// Turns a key letter into a shift amount (A/a -> 0, B/b -> 1, ...).
// Any non-letter key character is treated as a shift of 0.
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
    for (int i = 0; i < (int)text.size(); i++) {
        result += shiftLetter(text[i], key);
    }
    return result;
}

string caesarDecrypt(string text, int key) {
    // decrypting is just encrypting with the opposite shift
    return caesarEncrypt(text, 26 - (key % 26));
}

// ============================================================
// 2. STREAM CIPHER (now: Vigenere-style, mod-26 letter shifts
//    with a repeating key, instead of XOR on raw bytes)
// ============================================================
// Encrypt and decrypt are no longer the same function, because
// mod-26 addition isn't its own inverse the way XOR is.
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
// 3. ONE-TIME PAD (now: mod-26 letter addition with a pad the
//    same length as the text, instead of XOR on raw bytes).
//    This is the classic "letter" form of the Vernam one-time
//    pad: still unbreakable as long as the pad is truly random,
//    at least as long as the text, and used only once.
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

// Random pad made of letters (A-Z) instead of random bytes.
string generateRandomPad(int length) {
    string pad = "";
    for (int i = 0; i < length; i++) {
        pad += (char)('A' + rand() % 26);
    }
    return pad;
}

// ============================================================
// 4. AUTOKEY CIPHER
// ============================================================
// Same idea as Caesar, but instead of one fixed shift, each letter
// gets its own shift value that comes from the key. Once the key
// runs out, we keep going using the message itself as the key.
//
// The key is now a list of shift values (0-25) rather than a plain
// string, so it can come from letters, from typed numbers, or both -
// see parseKeyToShifts() below, which builds this list from user input.
string autoKeyEncrypt(string text, vector<int> keyShifts) {
    string result = "";
    vector<int> fullShifts = keyShifts; // key, then the message extends it
    for (char c : text) fullShifts.push_back(letterToShift(c));

    for (int i = 0; i < (int)text.size(); i++) {
        result += shiftLetter(text[i], fullShifts[i]);
    }
    return result;
}

string autoKeyDecrypt(string text, vector<int> keyShifts) {
    string result = "";
    vector<int> fullShifts = keyShifts; // we build this up as we decrypt each letter

    for (int i = 0; i < (int)text.size(); i++) {
        int shift = fullShifts[i];
        char plain = shiftLetter(text[i], -shift);
        result += plain;
        fullShifts.push_back(letterToShift(plain)); // extend with the plaintext we just found
    }
    return result;
}

// Turns the raw key input the user typed into a list of shift values
// (0-25). Supports three styles:
//   - letters only, no spaces:      "LEMON"        -> one shift per letter
//   - numbers, space separated:     "11 4 12 14 13" -> one shift per number
//   - mixed, space separated:       "L 4 O 14 N"    -> letters and numbers together
// Numbers outside 0-25 are wrapped with mod 26 (e.g. 30 -> 4, -1 -> 25).
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
        // No spaces at all: treat each character as its own token.
        // A run of digits with no spaces is read one digit at a time
        // (0-9 per character); use spaces to enter shifts of 10-25.
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

        cout << "1) Auto-generate a random pad  2) Type my own pad\n";
        int padChoice; cin >> padChoice; cin.ignore();

        string pad;
        if (padChoice == 1) {
            pad = generateRandomPad(text.size());
            cout << "Generated pad (letters) - SAVE THIS to decrypt later:\n";
            cout << pad << "\n";
        } else {
            cout << "Enter pad (letters, same length as your message): ";
            getline(cin, pad);
        }

        string cipher = onePadEncrypt(text, pad);
        cout << "Ciphertext: " << cipher << "\n";
    } else {
        cout << "Enter ciphertext: ";
        string text; getline(cin, text);

        cout << "Enter pad (letters - the same one used to encrypt): ";
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

    cout << "Enter key (letters and/or numbers 0-25, e.g. \"LEMON\" or \"11 4 12 14 13\"): ";
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