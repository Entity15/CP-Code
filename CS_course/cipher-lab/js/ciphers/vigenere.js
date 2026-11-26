// Vigenère cipher
ALGORITHMS.push(
{ n: 'Vigenère cipher', k: 'Key (letters)', t: 'ATTACK AT DAWN', e: 'LEMON',
  h: 'Like the stream cipher, but only letters use up a key letter.',
  f: (t, k, d) => { const K = letters(k); need(K, 'The key needs at least one letter'); let j = 0;
    return [...t].map(c => isL(c) ? shift(c, d * val(K[j++ % K.length])) : c).join(''); } }
);
