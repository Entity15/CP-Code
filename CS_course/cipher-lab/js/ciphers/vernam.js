// Vernam cipher
ALGORITHMS.push(
{ random: true, n: 'Vernam / One-time pad', k: 'Key (at least as long as the text)', t: 'Hello', e: 'KEYKEY',
  h: 'XORs every character with the key and shows hex. A random key as long as the text, used only once, makes this a one-time pad.',
  f: (t, k, d) => { const kb = enc8(k), b = d > 0 ? enc8(t) : unhex(t);
    if (kb.length < b.length) throw Error('The key must be at least as long as the text');
    const bin = v => v.toString(2).padStart(8, '0');
    const o = b.map((v, i) => { const x = v ^ kb[i]; step(bin(v) + ' XOR ' + bin(kb[i]) + ' = ' + bin(x)); return x; }); return d > 0 ? hex(o) : dec8(o); } }
);
