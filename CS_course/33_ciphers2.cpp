#include <bits/stdc++.h>
using namespace std;

// ---------- Small helpers ----------

// Keep only letters, in capitals: "Hi there!" -> "HITHERE"
string cleanText(string s) {
    string result = "";
    for (char c : s) {
        if (isalpha((unsigned char)c)) result += toupper((unsigned char)c);
    }
    return result;
}

// Remainder that is never negative: mod(-1) = 25
int mod(int x) {
    return ((x % 26) + 26) % 26;
}

// Find the number that multiplies with a to give 1 (mod 26). Returns -1 if none.
int inverseNumber(int a) {
    for (int x = 1; x < 26; x++) {
        if (mod(a * x) == 1) return x;
    }
    return -1;
}

// ---------- Hill cipher ----------

vector<vector<int>> smaller(vector<vector<int>> m, int skipRow, int skipCol) {
    int n = m.size();
    vector<vector<int>> result;
    for (int r = 0; r < n; r++) {
        if (r == skipRow) continue;
        vector<int> row;
        for (int c = 0; c < n; c++) {
            if (c != skipCol) row.push_back(m[r][c]);
        }
        result.push_back(row);
    }
    return result;
}

// Determinant (works for 2x2 and 3x3)
int determinant(vector<vector<int>> m) {
    int n = m.size();
    if (n == 1) return m[0][0];

    int det = 0;
    for (int col = 0; col < n; col++) {
        int sign = (col % 2 == 0) ? 1 : -1;
        det += sign * m[0][col] * determinant(smaller(m, 0, col));
    }
    return det;
}

// Inverse matrix mod 26. Returns an empty matrix if there is none.
vector<vector<int>> inverseMatrix(vector<vector<int>> m) {
    int n = m.size();
    int detInv = inverseNumber(mod(determinant(m)));
    if (detInv == -1) return {};

    vector<vector<int>> inv(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            int cofactor = sign * determinant(smaller(m, j, i));
            inv[i][j] = mod(detInv * mod(cofactor));
        }
    }
    return inv;
}

// Encrypt or decrypt: multiply each block of n letters by the matrix
string hillEncrypt(string text, vector<vector<int>> key) {
    int n = key.size();
    while ((int)text.size() % n != 0) text += 'X';

    string result = "";
    for (int start = 0; start < (int)text.size(); start += n) {
        for (int r = 0; r < n; r++) {
            int sum = 0;
            for (int c = 0; c < n; c++) {
                sum += key[r][c] * (text[start + c] - 'A');
            }
            result += (char)('A' + mod(sum));
        }
    }
    return result;
}

// ---------- Playfair cipher ----------

// Fill the 5x5 grid: keyword first, then the rest of the alphabet (J is merged into I)
void buildGrid(string keyword, char grid[5][5]) {
    string all = keyword + "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    string used = "";
    for (char c : all) {
        if (c == 'J') c = 'I';
        if (used.find(c) == string::npos) used += c;
    }
    for (int i = 0; i < 25; i++) {
        grid[i / 5][i % 5] = used[i];
    }
}

// Find the row and column of a letter
void findLetter(char grid[5][5], char letter, int &row, int &col) {
    row = 0;
    col = 0;
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (grid[r][c] == letter) {
                row = r;
                col = c;
            }
        }
    }
}

// Split text into pairs. J becomes I. Two equal letters in a pair get an X between them
// (or a Q if the letter is X). An odd last letter gets an X.
string makePairs(string text) {
    for (char &c : text) {
        if (c == 'J') c = 'I';
    }
    string result = "";
    int i = 0;
    while (i < (int)text.size()) {
        char a = text[i];
        char b;
        if (i + 1 < (int)text.size() && text[i + 1] != a) {
            b = text[i + 1];
            i += 2;
        } else {
            b = (a == 'X') ? 'Q' : 'X';
            i += 1;
        }
        result += a;
        result += b;
    }
    return result;
}

// dir = 1 to encrypt (move right/down), dir = -1 to decrypt (move left/up)
string playfair(string text, char grid[5][5], int dir) {
    string result = "";
    for (int i = 0; i + 1 < (int)text.size(); i += 2) {
        int r1, c1, r2, c2;
        findLetter(grid, text[i], r1, c1);
        findLetter(grid, text[i + 1], r2, c2);

        if (r1 == r2) {                       // same row
            result += grid[r1][(c1 + dir + 5) % 5];
            result += grid[r2][(c2 + dir + 5) % 5];
        } else if (c1 == c2) {                // same column
            result += grid[(r1 + dir + 5) % 5][c1];
            result += grid[(r2 + dir + 5) % 5][c2];
        } else {                              // rectangle
            result += grid[r1][c2];
            result += grid[r2][c1];
        }
    }
    return result;
}

// ---------- Main program ----------

int main() {
    cout << "Choose a cipher: 1 = Playfair, 2 = Hill 2x2, 3 = Hill 3x3: ";
    string choice;
    getline(cin, choice);

    if (choice == "1") {
        // ----- Playfair -----
        char grid[5][5];
        cout << "Keyword: ";
        string keyword;
        getline(cin, keyword);
        buildGrid(cleanText(keyword), grid);

        cout << "Text to encrypt: ";
        string text;
        getline(cin, text);
        string secret = playfair(makePairs(cleanText(text)), grid, 1);
        cout << "Encrypted: " << secret << endl;

        cout << "Decrypt? (y/n): ";
        string answer;
        getline(cin, answer);
        if (answer == "y" || answer == "Y") {
            cout << "Decrypted: " << playfair(secret, grid, -1) << endl;
        }
    }
    else if (choice == "2" || choice == "3") {
        // ----- Hill -----
        int n = (choice == "2") ? 2 : 3;
        vector<vector<int>> key(n, vector<int>(n));
        vector<vector<int>> inverse;

        // Ask until the key is valid and has an inverse
        while (true) {
            cout << "Enter " << n * n << " numbers, row by row: ";
            string line;
            getline(cin, line);
            stringstream numbers(line);

            for (int r = 0; r < n; r++) {
                for (int c = 0; c < n; c++) {
                    numbers >> key[r][c];
                }
            }
            if (numbers.fail()) {
                cout << "Please enter exactly " << n * n << " numbers.\n";
                continue;
            }

            string extra;
            if (numbers >> extra) {
                cout << "Please enter exactly " << n * n << " numbers.\n";
                continue;
            }

            inverse = inverseMatrix(key);
            if (inverse.size() > 0) break;
            cout << "This key has no inverse mod 26. Try another.\n";
        }

        cout << "Text to encrypt: ";
        string text;
        getline(cin, text);
        string secret = hillEncrypt(cleanText(text), key);
        cout << "Encrypted: " << secret << endl;

        cout << "Decrypt? (y/n): ";
        string answer;
        getline(cin, answer);
        if (answer == "y" || answer == "Y") {
            cout << "Decrypted: " << hillEncrypt(secret, inverse) << endl;
        }
    }
    else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}