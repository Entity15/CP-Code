// AES-128 (ECB mode) - encrypt or decrypt text
// Everything is inside main() on purpose.
#include <iostream>
#include <string>
using namespace std;

// multiply two bytes in GF(2^8) using the exp table (ex) and log table (lg)
#define GM(a, b) (((a) && (b)) ? ex[(lg[(a)] + lg[(b)]) % 255] : 0)

int main() {
    // ---------- 1. build the math tables (only once) ----------
    int ex[256], lg[256];
    int p = 1;
    for (int i = 0; i < 255; i++) {
        ex[i] = p;
        lg[p] = i;
        p = (p ^ (p << 1) ^ ((p & 0x80) ? 0x1B : 0)) & 0xFF;   // p = p * 3
    }

    // S-box: take the inverse of each byte, then do the affine step
    int sb[256], isb[256];
    for (int i = 0; i < 256; i++) {
        int inv = (i == 0) ? 0 : ex[(255 - lg[i]) % 255];
        int r = inv;
        int s = inv;
        for (int k = 0; k < 4; k++) {
            r = ((r << 1) | (r >> 7)) & 0xFF;   // rotate left by 1
            s ^= r;
        }
        s ^= 0x63;
        sb[i] = s;
        isb[s] = i;
    }

    string hx = "0123456789abcdef0123456789ABCDEF";   // hex digits (capitals work too for input)

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
        int kx[176];                     // all round keys: 11 keys x 16 bytes
        int first = 1;
        int again = 1;

        while (again) {
            // ask for input only the first time, after that we use the last result
            if (first) {
                if (dir == 1) cout << "Enter the text to encrypt: ";
                else          cout << "Enter the hex to decrypt: ";
                getline(cin, data);

                key = "";
                while (key.length() != 16) {
                    cout << "Enter the key (exactly 16 characters): ";
                    if (!getline(cin, key)) return 0;   // end of input: leave
                }

                // key expansion: fill kx[0..175]
                for (int i = 0; i < 16; i++) kx[i] = (unsigned char)key[i];
                int rc = 1;
                for (int i = 16; i < 176; i += 4) {
                    int t0 = kx[i - 4], t1 = kx[i - 3], t2 = kx[i - 2], t3 = kx[i - 1];
                    if (i % 16 == 0) {
                        int tmp = t0;
                        t0 = sb[t1] ^ rc;
                        t1 = sb[t2];
                        t2 = sb[t3];
                        t3 = sb[tmp];
                        rc = ((rc << 1) ^ ((rc & 0x80) ? 0x1B : 0)) & 0xFF;
                    }
                    kx[i]     = kx[i - 16] ^ t0;
                    kx[i + 1] = kx[i - 15] ^ t1;
                    kx[i + 2] = kx[i - 14] ^ t2;
                    kx[i + 3] = kx[i - 13] ^ t3;
                }
            }

            if (dir == 1) {
                // ---------- ENCRYPT ----------
                string buf = data;
                int n = (buf.length() + 15) / 16 * 16;   // pad with zeros to 16 bytes
                buf.resize(n, '\0');
                string res = "";

                for (int blk = 0; blk < n; blk += 16) {
                    int s[16];
                    for (int i = 0; i < 16; i++)
                        s[i] = (unsigned char)buf[blk + i] ^ kx[i];          // AddRoundKey (round 0)

                    for (int rnd = 1; rnd <= 10; rnd++) {
                        for (int i = 0; i < 16; i++)
                            s[i] = sb[s[i]];                                  // SubBytes

                        int t[16];                                            // ShiftRows
                        for (int c = 0; c < 4; c++)
                            for (int r = 0; r < 4; r++)
                                t[r + 4 * c] = s[r + 4 * ((c + r) % 4)];
                        for (int i = 0; i < 16; i++) s[i] = t[i];

                        if (rnd != 10) {                                      // MixColumns (not in last round)
                            for (int c = 0; c < 4; c++) {
                                int a0 = s[4 * c], a1 = s[4 * c + 1], a2 = s[4 * c + 2], a3 = s[4 * c + 3];
                                s[4 * c]     = GM(2, a0) ^ GM(3, a1) ^ a2 ^ a3;
                                s[4 * c + 1] = a0 ^ GM(2, a1) ^ GM(3, a2) ^ a3;
                                s[4 * c + 2] = a0 ^ a1 ^ GM(2, a2) ^ GM(3, a3);
                                s[4 * c + 3] = GM(3, a0) ^ a1 ^ a2 ^ GM(2, a3);
                            }
                        }

                        for (int i = 0; i < 16; i++)
                            s[i] ^= kx[16 * rnd + i];                         // AddRoundKey
                    }

                    for (int i = 0; i < 16; i++) {                            // write as hex
                        res += hx[s[i] / 16];
                        res += hx[s[i] % 16];
                    }
                }

                data = res;
                cout << "Encrypted (hex): " << data << "\n";
            }
            else {
                // ---------- DECRYPT ----------
                string buf = "";
                for (size_t i = 0; i + 1 < data.length(); i += 2)              // hex -> bytes
                    buf += (char)((hx.find(data[i]) % 16) * 16 + hx.find(data[i + 1]) % 16);

                int n = (buf.length() + 15) / 16 * 16;
                buf.resize(n, '\0');
                string res = "";

                for (int blk = 0; blk < n; blk += 16) {
                    int s[16];
                    for (int i = 0; i < 16; i++)
                        s[i] = (unsigned char)buf[blk + i] ^ kx[160 + i];    // AddRoundKey (round 10)

                    for (int rnd = 9; rnd >= 0; rnd--) {
                        int t[16];                                            // inverse ShiftRows
                        for (int c = 0; c < 4; c++)
                            for (int r = 0; r < 4; r++)
                                t[r + 4 * ((c + r) % 4)] = s[r + 4 * c];
                        for (int i = 0; i < 16; i++) s[i] = t[i];

                        for (int i = 0; i < 16; i++)
                            s[i] = isb[s[i]];                                 // inverse SubBytes

                        for (int i = 0; i < 16; i++)
                            s[i] ^= kx[16 * rnd + i];                         // AddRoundKey

                        if (rnd != 0) {                                       // inverse MixColumns
                            for (int c = 0; c < 4; c++) {
                                int a0 = s[4 * c], a1 = s[4 * c + 1], a2 = s[4 * c + 2], a3 = s[4 * c + 3];
                                s[4 * c]     = GM(14, a0) ^ GM(11, a1) ^ GM(13, a2) ^ GM(9, a3);
                                s[4 * c + 1] = GM(9, a0) ^ GM(14, a1) ^ GM(11, a2) ^ GM(13, a3);
                                s[4 * c + 2] = GM(13, a0) ^ GM(9, a1) ^ GM(14, a2) ^ GM(11, a3);
                                s[4 * c + 3] = GM(11, a0) ^ GM(13, a1) ^ GM(9, a2) ^ GM(14, a3);
                            }
                        }
                    }

                    for (int i = 0; i < 16; i++)
                        res += (char)s[i];
                }

                while (!res.empty() && res.back() == '\0')                    // remove the zero padding
                    res.pop_back();
                data = res;
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
