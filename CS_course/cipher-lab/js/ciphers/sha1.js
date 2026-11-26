// SHA-1
ALGORITHMS.push(
{ n: 'SHA-1', k: '', t: 'abc', e: '', hash: true,
  h: 'A one-way hash: 40 hex characters. There is nothing to decrypt. SHA-1 is not safe for real security work.',
  f: t => { const b = enc8(t), l = b.length * 8; b.push(128); while (b.length % 64 != 56) b.push(0);
    for (let i = 7; i >= 0; i--) b.push(i > 3 ? 0 : (l >>> (8 * i)) & 255);
    step('The message is ' + l + ' bits. After padding it is ' + b.length + ' bytes, which is ' + b.length / 64 + ' block(s) of 64 bytes.');
    const rol = (x, n) => (x << n) | (x >>> (32 - n)); let h = [0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0];
    for (let o = 0; o < b.length; o += 64) { const w = [];
      for (let i = 0; i < 16; i++) w[i] = (b[o + 4 * i] << 24) | (b[o + 4 * i + 1] << 16) | (b[o + 4 * i + 2] << 8) | b[o + 4 * i + 3];
      for (let i = 16; i < 80; i++) w[i] = rol(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
      let [a, bb, c, dd, e] = h;
      for (let i = 0; i < 80; i++) { let f, k;
        if (i < 20) { f = (bb & c) | (~bb & dd); k = 0x5A827999; } else if (i < 40) { f = bb ^ c ^ dd; k = 0x6ED9EBA1; }
        else if (i < 60) { f = (bb & c) | (bb & dd) | (c & dd); k = 0x8F1BBCDC; } else { f = bb ^ c ^ dd; k = 0xCA62C1D6; }
        const tmp = (rol(a, 5) + f + e + k + w[i]) | 0; e = dd; dd = c; c = rol(bb, 30); bb = a; a = tmp; }
      h = [h[0] + a, h[1] + bb, h[2] + c, h[3] + dd, h[4] + e].map(x => x | 0); }
    const words = h.map(x => (x >>> 0).toString(16).padStart(8, '0'));
    step('The five 32-bit words: ' + words.join(' '));
    return words.join(''); } }
);
