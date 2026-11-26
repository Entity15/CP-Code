// Stream cipher
ALGORITHMS.push(
{ n: 'Stream cipher', k: 'Key (letters)', t: 'Hello World', e: 'KEY',
  h: 'Repeats the key over the text, one key letter for every character.',
  f: (t, k, d) => { need(k); if (/[^a-z]/i.test(k)) throw Error('The key can only contain letters'); return [...t].map((c, i) => shift(c, d * kv(k[i % k.length]))).join(''); } }
);
