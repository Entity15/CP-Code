// Playfair cipher
ALGORITHMS.push(
{ n: 'Playfair cipher', k: 'Keyword', t: 'instruments', e: 'monarchy',
  h: 'A 5x5 grid built from the keyword (J counts as I). Letters are encrypted in pairs.',
  f: (t, k, d) => { let g = ''; for (const c of letters(k).replace(/J/g, 'I') + 'ABCDEFGHIKLMNOPQRSTUVWXYZ') if (!g.includes(c)) g += c;
    const pos = c => [Math.floor(g.indexOf(c) / 5), g.indexOf(c) % 5]; let s = letters(t).replace(/J/g, 'I');
    step('Grid (J counts as I):\n' + g.match(/...../g).map(r => '  ' + [...r].join(' ')).join('\n'));
    if (d > 0) { let p = ''; for (let i = 0; i < s.length;) { const a = s[i], b = s[i + 1];
        if (b && b != a) { p += a + b; i += 2; } else { p += a + (a == 'X' ? 'Q' : 'X'); i++; } } s = p; }
    else if (s.length % 2) throw Error('The ciphertext needs an even number of letters');
    step((d > 0 ? 'Pairs: ' : 'Cipher pairs: ') + (s.match(/../g) || []).join(' '));
    let o = ''; for (let i = 0; i < s.length; i += 2) { const [r1, c1] = pos(s[i]), [r2, c2] = pos(s[i + 1]);
      if (r1 == r2) o += g[r1 * 5 + mod(c1 + d, 5)] + g[r2 * 5 + mod(c2 + d, 5)];
      else if (c1 == c2) o += g[mod(r1 + d, 5) * 5 + c1] + g[mod(r2 + d, 5) * 5 + c2];
      else o += g[r1 * 5 + c2] + g[r2 * 5 + c1]; }
    step((d > 0 ? 'Encrypted pairs: ' : 'Decrypted pairs: ') + (o.match(/../g) || []).join(' '));
    return o; } }
);
