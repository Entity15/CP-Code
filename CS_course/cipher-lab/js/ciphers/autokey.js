// Autokey cipher
ALGORITHMS.push(
{ n: 'Autokey cipher', k: 'Key (letters or numbers)', t: 'Hello', e: 'KEY',
  h: 'The key is followed by the text itself. Numbers in the key become letters (0 = A).',
  f: (t, k, d) => { const K = letters(k.replace(/\d+/g, n => String.fromCharCode(65 + n % 26))); need(K, 'The key needs a letter or a number');
    let f = d > 0 ? K + t : K, o = '';
    for (let i = 0; i < t.length; i++) { const c = shift(t[i], d * kv(f[i])); o += c; if (d < 0) f += c; }
    return o; } }
);
