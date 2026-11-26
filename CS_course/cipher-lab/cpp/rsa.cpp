// RSA (textbook version with small numbers) - make the keys, encrypt, then optionally decrypt
// This is for learning. Real RSA uses primes with hundreds of digits plus padding.
// The primes are limited to 50000 so every calculation fits inside a long long.
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
using namespace std;

typedef long long ll;

// ---------- Small helpers ----------

// Ask a question and read the whole answer line
string readLine(string question) {
    cout << question;
    string line;
    if (!getline(cin, line)) exit(0);   // the input ended, so stop the program
    return line;
}

// Ask for a whole number. Asks again until the answer really is a number.
ll readNumber(string question) {
    while (true) {
        stringstream answer(readLine(question));
        ll x;
        string extra;
        if (answer >> x && !(answer >> extra)) return x;
        cout << "Please enter a whole number.\n";
    }
}

bool isPrime(ll x) {
    if (x < 2) return false;
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

// Greatest common divisor
ll gcdOf(ll a, ll b) {
    while (b != 0) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// base to the power exp, remainder mod. Squares the base step by step so the numbers stay small.
ll powerMod(ll base, ll exp, ll mod) {
    ll result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = result * base % mod;
        base = base * base % mod;
        exp = exp / 2;
    }
    return result;
}

// Find d so that (e * d) % phi == 1. This is the extended Euclid method.
ll inverseOf(ll e, ll phi) {
    ll oldR = e, r = phi;
    ll oldS = 1, s = 0;
    while (r != 0) {
        ll q = oldR / r;
        ll t = oldR - q * r;
        oldR = r;
        r = t;
        t = oldS - q * s;
        oldS = s;
        s = t;
    }
    return ((oldS % phi) + phi) % phi;
}

int main() {
    // ---------- 1. what do we want to encrypt? ----------
    cout << "Encrypt: 1 = text, 2 = a number\n";
    ll mode = 0;
    while (mode != 1 && mode != 2) mode = readNumber("Choose 1 or 2: ");

    // ---------- 2. choose the primes ----------
    ll p, q, n, phi, e, d;
    while (true) {
        p = readNumber("Enter a prime p (up to 50000): ");
        q = readNumber("Enter a different prime q (up to 50000): ");

        if (!isPrime(p) || !isPrime(q)) {
            cout << "Both numbers must be prime.\n";
            continue;
        }
        if (p == q) {
            cout << "p and q must be different.\n";
            continue;
        }
        if (p > 50000 || q > 50000) {
            cout << "Please use primes up to 50000.\n";
            continue;
        }

        n = p * q;
        phi = (p - 1) * (q - 1);

        if (mode == 1 && n < 256) {
            cout << "To encrypt text, p * q must be at least 256. Try bigger primes.\n";
            continue;
        }

        // is there any e that works for this phi?
        bool found = false;
        for (ll t = 3; t < phi; t++) {
            if (gcdOf(t, phi) == 1) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "These primes are too small to make a key. Try bigger primes.\n";
            continue;
        }
        break;
    }

    // ---------- 3. choose e and work out d ----------
    cout << "n = p * q = " << n << "\n";
    cout << "phi = (p - 1) * (q - 1) = " << phi << "\n";

    while (true) {
        string line = readLine("Enter e (press Enter to use the smallest one that works): ");
        if (line == "") {
            e = 3;
            while (gcdOf(e, phi) != 1) e++;
            break;
        }
        stringstream answer(line);
        string extra;
        if (answer >> e && !(answer >> extra) && e > 1 && e < phi && gcdOf(e, phi) == 1) break;
        cout << "e must be a number between 2 and " << phi - 1 << " with no common factor with phi.\n";
    }
    d = inverseOf(e, phi);

    cout << "e = " << e << "\n";
    cout << "d = " << d << "  (because e * d mod phi = 1)\n";
    cout << "Public key  (e, n) = (" << e << ", " << n << ")\n";
    cout << "Private key (d, n) = (" << d << ", " << n << ")\n";

    // ---------- 4. encrypt: c = m^e mod n ----------
    vector<ll> cipher;
    if (mode == 1) {
        string text = readLine("Enter the text to encrypt: ");
        for (int i = 0; i < (int)text.size(); i++) {
            ll m = (unsigned char)text[i];
            ll c = powerMod(m, e, n);
            cipher.push_back(c);
            cout << "'" << text[i] << "'  " << m << " -> " << c << "\n";
        }
    } else {
        ll m = -1;
        while (m < 0 || m >= n) m = readNumber("Enter the number to encrypt (0 to n - 1): ");
        ll c = powerMod(m, e, n);
        cipher.push_back(c);
        cout << m << " -> " << c << "\n";
    }

    cout << "Encrypted:";
    for (int i = 0; i < (int)cipher.size(); i++) cout << " " << cipher[i];
    cout << "\n";

    // ---------- 5. ask if we want to decrypt: m = c^d mod n ----------
    string ans = readLine("Do you want to decrypt it? (y/n): ");
    if (ans != "y" && ans != "Y") {
        cout << "Bye!\n";
        return 0;
    }

    if (mode == 1) {
        string res = "";
        for (int i = 0; i < (int)cipher.size(); i++) {
            res += (char)powerMod(cipher[i], d, n);
        }
        cout << "Decrypted text: " << res << "\n";
    } else {
        cout << "Decrypted number: " << powerMod(cipher[0], d, n) << "\n";
    }
    return 0;
}
