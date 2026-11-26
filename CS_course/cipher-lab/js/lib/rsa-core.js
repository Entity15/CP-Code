// ---------- RSA helpers (BigInt, so big numbers work) ----------
const powMod = (b, e, m) => { let r = 1n; b %= m; while (e > 0n) { if (e & 1n) r = r * b % m; b = b * b % m; e >>= 1n; } return r; };
const gcd = (a, b) => b ? gcd(b, a % b) : a;
const isPrime = n => { if (n < 2n) return false; for (let i = 2n; i * i <= n; i++) if (n % i == 0n) return false; return true; };
const modInv = (e, m) => { let [a, b, x, y] = [e, m, 1n, 0n]; while (b) { const q = a / b; [a, b] = [b, a - q * b]; [x, y] = [y, x - q * y]; } return ((x % m) + m) % m; };
