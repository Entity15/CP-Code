// Three more ciphers: Columnar Transposition, Vigenere and Vernam.
// Same style as 33_ciphers.cpp: small helper functions and a menu.
#include <bits/stdc++.h>
using namespace std;

// ---------- Small helpers ----------

// Ask a question and read the whole answer line
string readLine(string question) {
    cout << question;
    string line;
    if (!getline(cin, line)) exit(0);   // the input ended, so stop the program
    return line;
}

// Ask for a whole number. Asks again until the answer really is a number.
int readNumber(string question) {
    while (true) {
        stringstream answer(readLine(question));
        int x;
        string extra;
        if (answer >> x && !(answer >> extra)) return x;
        cout << "Please enter a whole number.\n";
    }
}

// Ask a y/n question
bool askYes(string question) {
    string answer = readLine(question);
    return answer == "y" || answer == "Y";
}

// Keep only letters, in capitals: "Hi there!" -> "HITHERE"
string cleanText(string s) {
    string result = "";
    for (char c : s) {
        if (isalpha((unsigned char)c)) result += toupper((unsigned char)c);
    }
    return result;
}

// Keep only letters and digits, in capitals (used for the transposition key)
string cleanKey(string s) {
    string result = "";
    for (char c : s) {
        if (isalnum((unsigned char)c)) result += toupper((unsigned char)c);
    }
    return result;
}

// Move one letter forward by shift places (backwards if shift is negative).
// Capitals stay capitals, small letters stay small, other characters are not changed.
char shiftLetter(char c, int shift) {
    shift = ((shift % 26) + 26) % 26;
    if (c >= 'a' && c <= 'z') return 'a' + (c - 'a' + shift) % 26;
    if (c >= 'A' && c <= 'Z') return 'A' + (c - 'A' + shift) % 26;
    return c;
}

// ============================================================
// 1. COLUMNAR TRANSPOSITION
// ============================================================
// The text is written in rows under the key. The columns are then read
// one by one, starting with the column that has the smallest key letter.

// The order in which the columns are read.
// Equal key letters are taken from left to right.
vector<int> columnOrder(string key) {
    int n = key.size();
    vector<int> order(n);
    for (int i = 0; i < n; i++) {
        int rank = 0;                      // how many columns are read before column i
        for (int j = 0; j < n; j++) {
            if (key[j] < key[i] || (key[j] == key[i] && j < i)) rank++;
        }
        order[rank] = i;
    }
    return order;
}

// Add X at the end until the last row is full
string padToFullRows(string text, int columns) {
    while ((int)text.size() % columns != 0) text += 'X';
    return text;
}

string columnarEncrypt(string text, string key) {
    int columns = key.size();
    text = padToFullRows(text, columns);
    int rows = text.size() / columns;
    vector<int> order = columnOrder(key);

    string result = "";
    for (int i = 0; i < columns; i++) {
        int col = order[i];
        for (int row = 0; row < rows; row++) {
            result += text[row * columns + col];
        }
    }
    return result;
}

string columnarDecrypt(string text, string key) {
    int columns = key.size();
    int rows = text.size() / columns;
    vector<int> order = columnOrder(key);

    string result(text.size(), ' ');
    int position = 0;                      // where we are in the ciphertext
    for (int i = 0; i < columns; i++) {
        int col = order[i];
        for (int row = 0; row < rows; row++) {
            result[row * columns + col] = text[position];
            position++;
        }
    }
    return result;
}

// Show the grid, so the steps can be written down
void showGrid(string text, string key) {
    int columns = key.size();
    cout << "Grid:\n";
    for (char c : key) cout << c << ' ';
    cout << "\n";
    for (int i = 0; i < (int)text.size(); i++) {
        cout << text[i] << ' ';
        if ((i + 1) % columns == 0) cout << "\n";
    }
    vector<int> order = columnOrder(key);
    cout << "Columns are read in this order:";
    for (int i = 0; i < (int)order.size(); i++) cout << " " << order[i] + 1;
    cout << "\n";
}

// ============================================================
// 2. VIGENERE CIPHER
// ============================================================
// Every letter is shifted by the next letter of the key (A = 0, B = 1, ...).
// The key repeats. Spaces and symbols stay as they are and do not use up a key letter.

// direction = 1 to encrypt, direction = -1 to decrypt
string vigenere(string text, string key, int direction) {
    string result = "";
    int keyIndex = 0;
    for (int i = 0; i < (int)text.size(); i++) {
        if (isalpha((unsigned char)text[i])) {
            int shift = key[keyIndex % key.size()] - 'A';
            result += shiftLetter(text[i], direction * shift);
            keyIndex++;
        } else {
            result += text[i];
        }
    }
    return result;
}

// ============================================================
// 3. VERNAM CIPHER
// ============================================================
// Every character is XOR-ed with the matching character of the key.
// XOR again with the same key gives the text back.
// The key must be at least as long as the text (when the key is random and used
// only once, this is the One-Time Pad).

string xorText(string text, string key) {
    string result = "";
    for (int i = 0; i < (int)text.size(); i++) {
        result += (char)(text[i] ^ key[i]);
    }
    return result;
}

// The XOR result can contain strange characters, so we show it as hex
string toHex(string s) {
    string hex = "0123456789abcdef";
    string result = "";
    for (int i = 0; i < (int)s.size(); i++) {
        int v = (unsigned char)s[i];
        result += hex[v / 16];
        result += hex[v % 16];
    }
    return result;
}

string fromHex(string h) {
    string result = "";
    for (int i = 0; i + 1 < (int)h.size(); i += 2) {
        result += (char)stoi(h.substr(i, 2), nullptr, 16);
    }
    return result;
}

string randomKey(int length) {
    string key = "";
    for (int i = 0; i < length; i++) key += (char)('A' + rand() % 26);
    return key;
}

// ============================================================
// MENU
// ============================================================

void runColumnar() {
    string text = cleanText(readLine("Enter text: "));
    if (text == "") {
        cout << "The text must contain at least one letter.\n";
        return;
    }
    string key = cleanKey(readLine("Enter key (a word like ZEBRA, or digits like 31254): "));
    if (key == "") {
        cout << "The key must contain at least one letter or digit.\n";
        return;
    }

    showGrid(padToFullRows(text, key.size()), key);
    string result = columnarEncrypt(text, key);
    cout << "Encrypted: " << result << "\n";

    if (askYes("Do you want to decrypt? (y/n): ")) {
        cout << "Decrypted: " << columnarDecrypt(result, key) << "\n";
        cout << "(Any X at the end may be padding.)\n";
    }
}

void runVigenere() {
    string text = readLine("Enter text: ");
    string key = cleanText(readLine("Enter key (letters only): "));
    if (key == "") {
        cout << "The key must contain at least one letter.\n";
        return;
    }

    string result = vigenere(text, key, 1);
    cout << "Encrypted: " << result << "\n";

    if (askYes("Do you want to decrypt? (y/n): ")) {
        cout << "Decrypted: " << vigenere(result, key, -1) << "\n";
    }
}

void runVernam() {
    string text = readLine("Enter text: ");
    if (text == "") {
        cout << "The text must not be empty.\n";
        return;
    }
    string key = readLine("Enter key (press Enter for a random key): ");
    if (key == "") {
        key = randomKey(text.size());
        cout << "Random key: " << key << "\n";
    }
    if (key.size() < text.size()) {
        cout << "The key must be at least as long as the text.\n";
        return;
    }

    string hex = toHex(xorText(text, key));
    cout << "Encrypted (hex): " << hex << "\n";

    if (askYes("Do you want to decrypt? (y/n): ")) {
        cout << "Decrypted: " << xorText(fromHex(hex), key) << "\n";
    }
}

int main() {
    srand(time(0));

    while (true) {
        cout << "\n--- Cipher Menu ---\n";
        cout << "1. Columnar Transposition\n";
        cout << "2. Vigenere Cipher\n";
        cout << "3. Vernam Cipher\n";
        cout << "0. Exit\n";

        int choice = readNumber("Choose: ");

        if (choice == 1) runColumnar();
        else if (choice == 2) runVigenere();
        else if (choice == 3) runVernam();
        else if (choice == 0) break;
        else cout << "Invalid choice.\n";
    }

    cout << "Goodbye.\n";
    return 0;
}
