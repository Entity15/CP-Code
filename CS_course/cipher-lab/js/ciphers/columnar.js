// Columnar transposition
ALGORITHMS.push(
{ n: 'Columnar transposition', k: 'Key (a word or digits)', t: 'WE ARE DISCOVERED', e: 'ZEBRAS',
  h: 'The text is written in rows under the key, then the columns are read in key order. Short rows get X.',
  f: (t, k, d) => { const K = k.toUpperCase().replace(/[^A-Z0-9]/g, ''); need(K, 'The key needs a letter or a digit');
    const n = K.length; let s = letters(t);
    const order = [...K].map((_, i) => i).sort((a, b) => K[a] < K[b] ? -1 : K[a] > K[b] ? 1 : a - b);
    if (d > 0) while (s.length % n) s += 'X'; else if (s.length % n) throw Error('The ciphertext length must be a multiple of the key length');
    const rows = s.length / n, o = Array(s.length).fill(''); let p = 0, r2 = '';
    for (const c of order) for (let r = 0; r < rows; r++) { if (d > 0) r2 += s[r * n + c]; else o[r * n + c] = s[p++]; }
    const g = d > 0 ? s : o.join('');
    step('Key:    ' + [...K].join(' ') + '\nGrid:\n' + (g.match(new RegExp('.{' + n + '}', 'g')) || []).map(r => '        ' + [...r].join(' ')).join('\n') + '\nColumns are read in this order: ' + order.map(i => i + 1).join(' '));
    return d > 0 ? r2 : o.join(''); } }
);
