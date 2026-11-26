// Hill cipher (2x2 or 3x3)
ALGORITHMS.push(
{ n: 'Hill cipher (2x2 or 3x3)', k: 'Matrix numbers, row by row', t: 'ACT', e: '6 24 1 13 16 10 20 17 15',
  h: 'Give 4 numbers for a 2x2 key or 9 numbers for a 3x3 key. Letters only, short blocks get X.',
  f: (t, k, d) => { const v = k.trim().split(/[\s,]+/).map(Number), n = Math.round(Math.sqrt(v.length));
    if (![2, 3].includes(n) || n * n != v.length || v.some(isNaN)) throw Error('Enter 4 numbers (2x2) or 9 numbers (3x3)');
    let m = []; for (let i = 0; i < n; i++) m.push(v.slice(i * n, i * n + n).map(x => mod(x)));
    const im = hillInverse(m); if (d < 0) m = im;
    step((d > 0 ? 'Key matrix (mod 26):\n' : 'Inverse of the key matrix (mod 26):\n') + m.map(r => '  ' + r.join(' ')).join('\n'));
    let s = letters(t), o = ''; while (s.length % n) s += 'X';
    const blocks = x => (x.match(new RegExp('.{' + n + '}', 'g')) || []).join(' ');
    step('Blocks of ' + n + ' letters: ' + blocks(s));
    for (let p = 0; p < s.length; p += n) for (let r = 0; r < n; r++) {
      let sum = 0; for (let c = 0; c < n; c++) sum += m[r][c] * (s.charCodeAt(p + c) - 65);
      o += String.fromCharCode(65 + mod(sum)); }
    step('Result blocks: ' + blocks(o));
    return o; } }
);
