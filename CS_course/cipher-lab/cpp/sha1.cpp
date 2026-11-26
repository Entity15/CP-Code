// SHA-1 - hash a line of text and print the 40 hex digit result
// Everything is inside main() on purpose. The program runs once and ends.
// Note: SHA-1 is not safe for new security work any more. It is here to learn how it works.
#include <iostream>
#include <string>
using namespace std;

// turn a 32-bit number left by n bits (the bits that fall off come back on the right)
#define ROL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

int main() {
    // ---------- 1. ask for the text ----------
    string text;
    cout << "Enter the text to hash: ";
    if (!getline(cin, text)) return 0;

    // the five starting values
    unsigned int h0 = 0x67452301;
    unsigned int h1 = 0xEFCDAB89;
    unsigned int h2 = 0x98BADCFE;
    unsigned int h3 = 0x10325476;
    unsigned int h4 = 0xC3D2E1F0;

    // ---------- 2. padding ----------
    // add one 1 bit (the byte 0x80), then zeros until the length is 56 bytes
    // more than a multiple of 64, then the length of the text in bits as 8 bytes
    string msg = text;
    unsigned long long bits = (unsigned long long)text.length() * 8;
    msg += (char)0x80;
    while (msg.length() % 64 != 56) msg += (char)0;
    for (int i = 7; i >= 0; i--)
        msg += (char)((bits >> (8 * i)) & 0xFF);

    // ---------- 3. handle every 64 byte block ----------
    for (size_t blk = 0; blk < msg.length(); blk += 64) {
        // 16 words of 4 bytes, then grow them to 80 words
        unsigned int w[80];
        for (int i = 0; i < 16; i++) {
            w[i] = ((unsigned int)(unsigned char)msg[blk + 4 * i] << 24)
                 | ((unsigned int)(unsigned char)msg[blk + 4 * i + 1] << 16)
                 | ((unsigned int)(unsigned char)msg[blk + 4 * i + 2] << 8)
                 |  (unsigned int)(unsigned char)msg[blk + 4 * i + 3];
        }
        for (int i = 16; i < 80; i++)
            w[i] = ROL(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);

        unsigned int a = h0, b = h1, c = h2, d = h3, e = h4;

        // 80 rounds, in 4 groups of 20, each group with its own function and constant
        for (int i = 0; i < 80; i++) {
            unsigned int f, k;
            if (i < 20) {
                f = (b & c) | (~b & d);
                k = 0x5A827999;
            } else if (i < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            unsigned int temp = ROL(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = ROL(b, 30);
            b = a;
            a = temp;
        }

        // add this block's result to the running values
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    // ---------- 4. print the five values as hex ----------
    string hx = "0123456789abcdef";
    unsigned int h[5] = {h0, h1, h2, h3, h4};
    string digest = "";
    for (int i = 0; i < 5; i++) {
        for (int j = 7; j >= 0; j--)
            digest += hx[(h[i] >> (4 * j)) & 0xF];
    }
    cout << "SHA-1: " << digest << "\n";
    return 0;
}
