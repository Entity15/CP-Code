// RSA
ALGORITHMS.push(
{ info: true, n: 'RSA', k: 'p q (and e if you want)', t: 'Hi', e: '61 53 17',
  h: 'Textbook RSA on every character. Give two primes p and q, and optionally e. Decrypt by pasting the numbers.',
  f: (t, k, d) => { const v = k.trim().split(/[\s,]+/).filter(Boolean); if (v.length < 2) throw Error('Enter p and q, like: 61 53 17');
    let p, q, e = 3n; try { p = BigInt(v[0]); q = BigInt(v[1]); if (v[2]) e = BigInt(v[2]); } catch { throw Error('p, q and e must be whole numbers'); }
    if (p > 10n ** 12n || q > 10n ** 12n) throw Error('Please use primes below 10^12');
    if (!isPrime(p) || !isPrime(q) || p == q) throw Error('p and q must be two different primes');
    const n = p * q, phi = (p - 1n) * (q - 1n); if (!v[2]) while (gcd(e, phi) != 1n && e < phi) e++;
    if (e < 2n || e >= phi || gcd(e, phi) != 1n) throw Error('e must be between 2 and ' + (phi - 1n) + ' and share no factor with phi = ' + phi);
    const dd = modInv(e, phi), info = 'n = ' + n + ', phi = ' + phi + ', e = ' + e + ', d = ' + dd + '\n';
    step('n = p * q = ' + n + '\nphi = (p - 1)(q - 1) = ' + phi + '\ne = ' + e + ' and d = ' + dd + ', because e * d mod phi = 1\n');
    if (d > 0) { if (n < 256n) throw Error('To encrypt text, p * q must be at least 256');
      return info + enc8(t).map(b => { const c = powMod(BigInt(b), e, n); step('byte ' + b + ':  ' + b + '^' + e + ' mod ' + n + ' = ' + c); return c; }).join(' '); }
    try { return info + dec8(t.trim().split(/\s+/).map(x => { const m = Number(powMod(BigInt(x), dd, n)); step(x + '^' + dd + ' mod ' + n + ' = ' + m); return m; })); } catch { throw Error('Paste the numbers from the Encrypt step'); } } }
);
