// DES (ECB mode) - encrypt or decrypt text
// Everything is inside main() on purpose.
// Bits are stored one per int (0 or 1), so it is easy to follow the steps.
#include <iostream>
#include <string>
using namespace std;

int main() {
    // ---------- 1. DES tables (numbers start at 1, like the textbook) ----------
    int ip[64] = {
        58,50,42,34,26,18,10,2, 60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6, 64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,  59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5, 63,55,47,39,31,23,15,7 };

    int fp[64] = {
        40,8,48,16,56,24,64,32, 39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30, 37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28, 35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26, 33,1,41,9,49,17,57,25 };

    int ee[48] = {
        32,1,2,3,4,5,  4,5,6,7,8,9,
        8,9,10,11,12,13,  12,13,14,15,16,17,
        16,17,18,19,20,21,  20,21,22,23,24,25,
        24,25,26,27,28,29,  28,29,30,31,32,1 };

    int pp[32] = {
        16,7,20,21,29,12,28,17, 1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,    19,13,30,6,22,11,4,25 };

    int pc1[56] = {
        57,49,41,33,25,17,9,  1,58,50,42,34,26,18,
        10,2,59,51,43,35,27,  19,11,3,60,52,44,36,
        63,55,47,39,31,23,15, 7,62,54,46,38,30,22,
        14,6,61,53,45,37,29,  21,13,5,28,20,12,4 };

    int pc2[48] = {
        14,17,11,24,1,5,   3,28,15,6,21,10,
        23,19,12,4,26,8,   16,7,27,20,13,2,
        41,52,31,37,47,55, 30,40,51,45,33,48,
        44,49,39,56,34,53, 46,42,50,36,29,32 };

    int shf[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

    // the 8 S-boxes: sbx[box][row][col]
    int sbx[8][4][16] = {
        { {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
          {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
          {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
          {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} },
        { {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
          {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
          {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
          {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9} },
        { {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
          {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
          {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
          {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12} },
        { {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
          {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
          {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
          {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14} },
        { {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
          {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
          {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
          {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3} },
        { {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
          {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
          {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
          {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13} },
        { {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
          {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
          {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
          {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12} },
        { {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
          {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
          {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
          {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11} } };

    string hx = "0123456789abcdef0123456789ABCDEF";   // hex digits

    // ---------- 2. main loop ----------
    string ch, data, key, ans;
    while (1) {
        cout << "\n1 = Encrypt   2 = Decrypt   0 = Exit\nYour choice: ";
        if (!getline(cin, ch)) break;      // end of input: leave
        if (ch == "0") break;
        if (ch != "1" && ch != "2") {
            cout << "Wrong choice, try again.\n";
            continue;
        }

        int dir = (ch == "1") ? 1 : 2;   // 1 = encrypt, 2 = decrypt
        int sk[16][48];                  // the 16 round keys, 48 bits each
        int first = 1;
        int again = 1;

        while (again) {
            // ask for input only the first time, after that we use the last result
            if (first) {
                if (dir == 1) cout << "Enter the text to encrypt: ";
                else          cout << "Enter the hex to decrypt: ";
                getline(cin, data);

                key = "";
                while (key.length() != 8) {
                    cout << "Enter the key (exactly 8 characters): ";
                    if (!getline(cin, key)) return 0;   // end of input: leave
                }

                // key bits, one per int, 8 bits per character
                int kb[64];
                for (int i = 0; i < 8; i++)
                    for (int j = 0; j < 8; j++)
                        kb[8 * i + j] = ((unsigned char)key[i] >> (7 - j)) & 1;

                // PC-1: split the 64 key bits into two halves c and d (28 bits each)
                int c[28], d[28];
                for (int i = 0; i < 28; i++) {
                    c[i] = kb[pc1[i] - 1];
                    d[i] = kb[pc1[28 + i] - 1];
                }

                // make the 16 round keys
                for (int r = 0; r < 16; r++) {
                    for (int s = 0; s < shf[r]; s++) {          // rotate left
                        int t = c[0];
                        for (int i = 0; i < 27; i++) c[i] = c[i + 1];
                        c[27] = t;
                        t = d[0];
                        for (int i = 0; i < 27; i++) d[i] = d[i + 1];
                        d[27] = t;
                    }
                    for (int j = 0; j < 48; j++) {              // PC-2
                        int q = pc2[j] - 1;
                        sk[r][j] = (q < 28) ? c[q] : d[q - 28];
                    }
                }
            }

            // turn the input text (or hex) into bytes
            string buf = "";
            if (dir == 1) {
                buf = data;
            } else {
                for (size_t i = 0; i + 1 < data.length(); i += 2)
                    buf += (char)((hx.find(data[i]) % 16) * 16 + hx.find(data[i + 1]) % 16);
            }
            int n = (buf.length() + 7) / 8 * 8;   // pad with zeros to 8 bytes
            buf.resize(n, '\0');

            string out = "";
            for (int blk = 0; blk < n; blk += 8) {
                // 8 bytes -> 64 bits
                int bt[64];
                for (int i = 0; i < 8; i++)
                    for (int j = 0; j < 8; j++)
                        bt[8 * i + j] = ((unsigned char)buf[blk + i] >> (7 - j)) & 1;

                // initial permutation, then split into left and right halves
                int x[64];
                for (int i = 0; i < 64; i++) x[i] = bt[ip[i] - 1];
                int l[32], r[32];
                for (int i = 0; i < 32; i++) {
                    l[i] = x[i];
                    r[i] = x[32 + i];
                }

                // 16 rounds
                for (int rnd = 0; rnd < 16; rnd++) {
                    int kk = (dir == 1) ? rnd : 15 - rnd;   // decrypt uses the keys backwards

                    // expand R to 48 bits and mix with the round key
                    int er[48];
                    for (int j = 0; j < 48; j++)
                        er[j] = r[ee[j] - 1] ^ sk[kk][j];

                    // 8 S-boxes: 6 bits in, 4 bits out
                    int so[32];
                    for (int s = 0; s < 8; s++) {
                        int row = er[6 * s] * 2 + er[6 * s + 5];
                        int col = er[6 * s + 1] * 8 + er[6 * s + 2] * 4 + er[6 * s + 3] * 2 + er[6 * s + 4];
                        int v = sbx[s][row][col];
                        so[4 * s]     = (v >> 3) & 1;
                        so[4 * s + 1] = (v >> 2) & 1;
                        so[4 * s + 2] = (v >> 1) & 1;
                        so[4 * s + 3] = v & 1;
                    }

                    // P permutation, then new R = L xor f, new L = old R
                    int f[32];
                    for (int j = 0; j < 32; j++) f[j] = so[pp[j] - 1];
                    for (int j = 0; j < 32; j++) {
                        int t = r[j];
                        r[j] = l[j] ^ f[j];
                        l[j] = t;
                    }
                }

                // swap the halves (R then L), then final permutation
                int pre[64];
                for (int i = 0; i < 32; i++) {
                    pre[i] = r[i];
                    pre[32 + i] = l[i];
                }
                int y[64];
                for (int i = 0; i < 64; i++) y[i] = pre[fp[i] - 1];

                // 64 bits -> 8 bytes
                for (int i = 0; i < 8; i++) {
                    int v = 0;
                    for (int j = 0; j < 8; j++) v = v * 2 + y[8 * i + j];
                    out += (char)v;
                }
            }

            if (dir == 1) {
                data = "";
                for (size_t i = 0; i < out.length(); i++) {     // bytes -> hex
                    int v = (unsigned char)out[i];
                    data += hx[v / 16];
                    data += hx[v % 16];
                }
                cout << "Encrypted (hex): " << data << "\n";
            } else {
                while (!out.empty() && out.back() == '\0')      // remove the zero padding
                    out.pop_back();
                data = out;
                cout << "Decrypted text: " << data << "\n";
            }

            // ask if we want to do the opposite with this result
            first = 0;
            if (dir == 1) cout << "Want to decrypt it now too? (y/n): ";
            else          cout << "Want to encrypt it now too? (y/n): ";
            getline(cin, ans);
            if (ans == "y" || ans == "Y") dir = 3 - dir;   // 1 becomes 2, 2 becomes 1
            else again = 0;
        }
    }

    cout << "Bye!\n";
    return 0;
}
