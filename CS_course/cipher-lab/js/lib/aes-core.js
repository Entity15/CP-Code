// ---------- AES-128 tables (built the same way as in aes.cpp) ----------
const ex = [], lg = [];
for (let i = 0, p = 1; i < 255; i++) { ex[i] = p; lg[p] = i; p = (p ^ (p << 1) ^ (p & 128 ? 27 : 0)) & 255; }
const gm = (a, b) => a && b ? ex[(lg[a] + lg[b]) % 255] : 0;
const sb = [], isb = [];
for (let i = 0; i < 256; i++) {
  let v = i ? ex[(255 - lg[i]) % 255] : 0, r = v, s = v;
  for (let k = 0; k < 4; k++) { r = ((r << 1) | (r >> 7)) & 255; s ^= r; }
  s ^= 99; sb[i] = s; isb[s] = i;
}
function aesKeys(key) {
  const k = [...key]; let rc = 1;
  for (let i = 16; i < 176; i += 4) {
    let t = k.slice(i - 4, i);
    if (i % 16 == 0) { t = [sb[t[1]] ^ rc, sb[t[2]], sb[t[3]], sb[t[0]]]; rc = ((rc << 1) ^ (rc & 128 ? 27 : 0)) & 255; }
    for (let j = 0; j < 4; j++) k[i + j] = k[i - 16 + j] ^ t[j];
  }
  return k;
}
function aesBlock(s, k, d) {
  const tr = STEPS.length === 0;   // show the working for the first block only
  const mix = m => { for (let c = 0; c < 4; c++) { const [a, b, e, f] = s.slice(4 * c, 4 * c + 4);
    s[4 * c]     = gm(m[0], a) ^ gm(m[1], b) ^ gm(m[2], e) ^ gm(m[3], f);
    s[4 * c + 1] = gm(m[3], a) ^ gm(m[0], b) ^ gm(m[1], e) ^ gm(m[2], f);
    s[4 * c + 2] = gm(m[2], a) ^ gm(m[3], b) ^ gm(m[0], e) ^ gm(m[1], f);
    s[4 * c + 3] = gm(m[1], a) ^ gm(m[2], b) ^ gm(m[3], e) ^ gm(m[0], f); } };
  const rows = back => { const t = []; for (let c = 0; c < 4; c++) for (let q = 0; q < 4; q++) { if (back) t[q + 4 * ((c + q) % 4)] = s[q + 4 * c]; else t[q + 4 * c] = s[q + 4 * ((c + q) % 4)]; } s = t; };
  if (d > 0) {
    s = s.map((v, i) => v ^ k[i]);
    if (tr) step('Start, after adding round key 0:  ' + hex(s));
    for (let r = 1; r <= 10; r++) {
      s = s.map(v => sb[v]); rows(false);
      if (r < 10) mix([2, 3, 1, 1]);
      s = s.map((v, i) => v ^ k[16 * r + i]);
      if (tr) step('After round ' + r + ':  ' + hex(s));
    }
    return s;
  }
  s = s.map((v, i) => v ^ k[160 + i]);
  if (tr) step('Start, after adding round key 10:  ' + hex(s));
  for (let r = 9; r >= 0; r--) {
    rows(true); s = s.map(v => isb[v]).map((v, i) => v ^ k[16 * r + i]);
    if (r) mix([14, 11, 13, 9]);
    if (tr) step('After undoing round ' + (r + 1) + ':  ' + hex(s));
  }
  return s;
}
