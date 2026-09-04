/*
 * ciphers.cpp
 * ------------------------------------------------------------
 * Menu-driven implementation of four classical ciphers:
 *   1. Caesar Cipher
 *   2. Stream Cipher   (XOR with a keystream generated from a key)
 *   3. One-Time Pad    (XOR with a pad, byte-for-byte)
 *   4. Autokey Cipher  (Vigenere-style, key extended by the message)
 *
 * You choose which cipher to use and whether to encrypt or decrypt.
 *
 * NOTES ON OUTPUT FORMAT:
 *   - Caesar and Autokey only touch letters, so their output is
 *     printed as plain text.
 *   - Stream cipher and OTP XOR raw bytes, which produces
 *     unprintable characters. Their output/input is shown as HEX
 *     so you can copy/paste it safely between runs.
 *
 * Compile:
 *   g++ -std=c++17 -O2 -o ciphers ciphers.cpp
 * ------------------------------------------------------------
 */

#include <bits/stdc++.h>

using namespace std;

// ============================================================
// Helpers: hex <-> raw bytes (needed for stream cipher / OTP)
// ============================================================
string toHex(const string& s) {
    ostringstream oss;
    for (unsigned char c : s)
        oss << hex << setw(2) << setfill('0') << static_cast<int>(c);
    return oss.str();
}

string fromHex(const string& hexStr) {
    string result;
    for (size_t i = 0; i + 1 < hexStr.size(); i += 2) {
        string byteStr = hexStr.substr(i, 2);
        char byte = static_cast<char>(strtol(byteStr.c_str(), nullptr, 16));
        result += byte;
    }
    return result;
}

// ============================================================
// 1. CAESAR CIPHER
//    Shifts letters by `shift` positions, wraps around A-Z / a-z.
//    Non-letters are left untouched.
// ============================================================
string caesarEncrypt(const string& text, int shift) {
    shift = ((shift % 26) + 26) % 26; // normalize
    string result;
    result.reserve(text.size());
    for (char c : text) {
        if (isupper(static_cast<unsigned char>(c)))
            result += static_cast<char>('A' + (c - 'A' + shift) % 26);
        else if (islower(static_cast<unsigned char>(c)))
            result += static_cast<char>('a' + (c - 'a' + shift) % 26);
        else
            result += c;
    }
    return result;
}

string caesarDecrypt(const string& text, int shift) {
    return caesarEncrypt(text, 26 - ((shift % 26) + 26) % 26);
}

// ============================================================
// 2. STREAM CIPHER
//    A simple synchronous stream cipher: a keystream of pseudo-random
//    bytes is generated from the key (via an LCG), then XORed with
//    the plaintext/ciphertext byte-by-byte. XOR is its own inverse,
//    so the SAME function does both encryption and decryption as
//    long as the same key is used.
// ============================================================
vector<unsigned char> generateKeystream(const string& key, size_t length) {
    unsigned long seed = 0;
    for (char c : key)
        seed = seed * 31 + static_cast<unsigned char>(c);
    if (seed == 0) seed = 12345UL; // avoid degenerate all-zero seed

    vector<unsigned char> stream;
    stream.reserve(length);
    unsigned long state = seed;
    for (size_t i = 0; i < length; i++) {
        // classic LCG (same constants as glibc's rand())
        state = (1103515245UL * state + 12345UL) & 0x7fffffffUL;
        stream.push_back(static_cast<unsigned char>(state % 256));
    }
    return stream;
}

string streamCipherApply(const string& data, const string& key) {
    vector<unsigned char> ks = generateKeystream(key, data.size());
    string result = data;
    for (size_t i = 0; i < data.size(); i++)
        result[i] = static_cast<char>(static_cast<unsigned char>(data[i]) ^ ks[i]);
    return result;
}

// ============================================================
// 3. ONE-TIME PAD (OTP)
//    XORs the message with a pad that must be at least as long as
//    the message. True OTP security requires the pad be random,
//    secret, and used only once. Same XOR function encrypts/decrypts.
// ============================================================
vector<unsigned char> generateRandomPad(size_t length) {
    vector<unsigned char> pad(length);
    for (size_t i = 0; i < length; i++)
        pad[i] = static_cast<unsigned char>(rand() % 256);
    return pad;
}

string otpApply(const string& data, const vector<unsigned char>& pad) {
    string result = data;
    for (size_t i = 0; i < data.size(); i++)
        result[i] = static_cast<char>(static_cast<unsigned char>(data[i]) ^ pad[i % pad.size()]);
    return result;
}

// ============================================================
// 4. AUTOKEY CIPHER
//    Like Vigenere, but instead of repeating a short key, the key
//    is extended using the message itself:
//      Encrypt: key stream = [key letters] + [plaintext letters]
//      Decrypt: key stream = [key letters] + [recovered plaintext]
//    Only alphabetic characters are transformed; case is preserved.
// ============================================================
string autoKeyEncrypt(const string& text, const string& key) {
    string result;
    result.reserve(text.size());
    vector<char> keystream;
    for (char k : key)
        if (isalpha(static_cast<unsigned char>(k)))
            keystream.push_back(static_cast<char>(toupper(k)));

    size_t ksPos = 0;
    for (char c : text) {
        if (isalpha(static_cast<unsigned char>(c))) {
            char base = isupper(static_cast<unsigned char>(c)) ? 'A' : 'a';
            int p = toupper(c) - 'A';
            int k = keystream[ksPos] - 'A';
            ksPos++;
            int enc = (p + k) % 26;
            result += static_cast<char>(base + enc);
            keystream.push_back(static_cast<char>(toupper(c))); // extend key with plaintext
        } else {
            result += c;
        }
    }
    return result;
}

string autoKeyDecrypt(const string& text, const string& key) {
    string result;
    result.reserve(text.size());
    vector<char> keystream;
    for (char k : key)
        if (isalpha(static_cast<unsigned char>(k)))
            keystream.push_back(static_cast<char>(toupper(k)));

    size_t ksPos = 0;
    for (char c : text) {
        if (isalpha(static_cast<unsigned char>(c))) {
            char base = isupper(static_cast<unsigned char>(c)) ? 'A' : 'a';
            int cval = toupper(c) - 'A';
            int k = keystream[ksPos] - 'A';
            ksPos++;
            int dec = ((cval - k) % 26 + 26) % 26;
            char plainUpper = static_cast<char>('A' + dec);
            result += static_cast<char>(base + dec);
            keystream.push_back(plainUpper); // extend key with recovered plaintext
        } else {
            result += c;
        }
    }
    return result;
}

// ============================================================
// MENU / DRIVER
// ============================================================
int readIntChoice(const string& prompt, int lo, int hi) {
    int choice;
    while (true) {
        cout << prompt;
        if (cin >> choice && choice >= lo && choice <= hi) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        cout << "Invalid choice, try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void runCaesar() {
    int mode = readIntChoice("1) Encrypt  2) Decrypt\nChoice: ", 1, 2);
    cout << "Enter text: ";
    string text; getline(cin, text);
    cout << "Enter integer shift key: ";
    int shift; cin >> shift; cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string out = (mode == 1) ? caesarEncrypt(text, shift) : caesarDecrypt(text, shift);
    cout << (mode == 1 ? "Ciphertext: " : "Plaintext: ") << out << "\n";
}

void runStream() {
    int mode = readIntChoice("1) Encrypt  2) Decrypt\nChoice: ", 1, 2);
    cout << "Enter key (any text): ";
    string key; getline(cin, key);

    if (mode == 1) {
        cout << "Enter plaintext: ";
        string text; getline(cin, text);
        string cipherBytes = streamCipherApply(text, key);
        cout << "Ciphertext (hex): " << toHex(cipherBytes) << "\n";
    } else {
        cout << "Enter ciphertext (hex): ";
        string hexIn; getline(cin, hexIn);
        string cipherBytes = fromHex(hexIn);
        string plain = streamCipherApply(cipherBytes, key); // XOR again = decrypt
        cout << "Plaintext: " << plain << "\n";
    }
}

void runOTP() {
    int mode = readIntChoice("1) Encrypt  2) Decrypt\nChoice: ", 1, 2);

    if (mode == 1) {
        cout << "Enter plaintext: ";
        string text; getline(cin, text);

        int padChoice = readIntChoice(
            "1) Auto-generate random pad  2) Enter my own pad (hex)\nChoice: ", 1, 2);

        vector<unsigned char> pad;
        if (padChoice == 1) {
            pad = generateRandomPad(text.size());
            cout << "Generated pad (hex) - SAVE THIS to decrypt later:\n";
            ostringstream oss;
            for (unsigned char b : pad) oss << hex << setw(2) << setfill('0') << (int)b;
            cout << oss.str() << "\n";
        } else {
            cout << "Enter pad (hex, at least as long as text): ";
            string hexPad; getline(cin, hexPad);
            string padBytes = fromHex(hexPad);
            pad.assign(padBytes.begin(), padBytes.end());
        }

        string cipherBytes = otpApply(text, pad);
        cout << "Ciphertext (hex): " << toHex(cipherBytes) << "\n";
    } else {
        cout << "Enter ciphertext (hex): ";
        string hexIn; getline(cin, hexIn);
        cout << "Enter pad (hex, same one used to encrypt): ";
        string hexPad; getline(cin, hexPad);

        string cipherBytes = fromHex(hexIn);
        string padBytes = fromHex(hexPad);
        vector<unsigned char> pad(padBytes.begin(), padBytes.end());

        string plain = otpApply(cipherBytes, pad);
        cout << "Plaintext: " << plain << "\n";
    }
}

void runAutoKey() {
    int mode = readIntChoice("1) Encrypt  2) Decrypt\nChoice: ", 1, 2);
    cout << "Enter text: ";
    string text; getline(cin, text);
    cout << "Enter key (letters only matter): ";
    string key; getline(cin, key);

    string out = (mode == 1) ? autoKeyEncrypt(text, key) : autoKeyDecrypt(text, key);
    cout << (mode == 1 ? "Ciphertext: " : "Plaintext: ") << out << "\n";
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    while (true) {
        cout << "\n===== Cipher Menu =====\n"
             << "1. Caesar Cipher\n"
             << "2. Stream Cipher\n"
             << "3. One-Time Pad\n"
             << "4. Autokey Cipher\n"
             << "0. Exit\n";
        int choice = readIntChoice("Choose a cipher: ", 0, 4);

        switch (choice) {
            case 1: runCaesar(); break;
            case 2: runStream(); break;
            case 3: runOTP(); break;
            case 4: runAutoKey(); break;
            case 0: cout << "Goodbye.\n"; return 0;
        }
    }
}
