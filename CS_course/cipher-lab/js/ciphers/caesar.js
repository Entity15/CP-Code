// Caesar cipher
ALGORITHMS.push(
{ n: 'Caesar cipher', k: 'Shift (a number)', t: 'Hello World', e: '3',
  h: 'Moves every letter forward by the shift.',
  f: (t, k, d) => { const n = parseInt(k); if (isNaN(n)) throw Error('The shift must be a number'); return [...t].map(c => shift(c, d * n)).join(''); } }
);
