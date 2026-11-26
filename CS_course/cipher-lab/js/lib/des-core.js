// ---------- DES tables (copied from des.cpp) ----------
const IP=[58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7],FP=[40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25],E=[32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1],P=[16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25],PC1=[57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4],PC2=[14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32],SH=[1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1];
const SB="e4d12fb83a6c59070f74e2d1a6cb953841e8d62bfc973a50fc8249175b3ea06df18e6b34972dc05a3d47f28ec01a69b50e7ba4d158c6932fd8a13f42b67c05e9a09e63f51dc7b428d709346a285ecbf1d6498f30b12c5ae71ad069874fe3b52c7de3069a1285bc4fd8b56f03472c1ae9a690cb7df13e52843f06a1d8945bc72e2c417ab6853fd0e9eb2c47d150fa3986421bad78f9c5630eb8c71e2d6f09a453c1af92680d34e75baf427c9561de0b389ef528c3704a1db6432c95fabe17608d4b2ef08d3c975a61d0b7491ae35c2f8614bdc37eaf6805926bd814a7950fe23cd2846fb1a93e50c71fd8a374c56b0e927b419ce206adf35821e74a8dfc90356b".match(/.{64}/g).map(s=>[...s].map(c=>parseInt(c,16)));
const bits = b => b.flatMap(v => [7, 6, 5, 4, 3, 2, 1, 0].map(j => (v >> j) & 1));
const perm = (t, tab) => tab.map(i => t[i - 1]);
const toBytes = bt => { const o = []; for (let i = 0; i < bt.length; i += 8) o.push(bt.slice(i, i + 8).reduce((a, x) => a * 2 + x, 0)); return o; };
function desKeys(kb) {
  const cd = perm(bits(kb), PC1); let c = cd.slice(0, 28), d = cd.slice(28);
  return SH.map(s => { c = c.slice(s).concat(c.slice(0, s)); d = d.slice(s).concat(d.slice(0, s)); return perm(c.concat(d), PC2); });
}
function desBlock(b, ks, dir) {
  const tr = STEPS.length === 0;   // show the working for the first block only
  const bh = a => toBytes(a).map(v => v.toString(16).padStart(2, '0')).join('');
  const x = perm(bits(b), IP); let l = x.slice(0, 32), r = x.slice(32);
  if (tr) step('After the initial permutation:  L0 = ' + bh(l) + '  R0 = ' + bh(r));
  for (let n = 0; n < 16; n++) {
    const k = ks[dir > 0 ? n : 15 - n], er = perm(r, E).map((v, i) => v ^ k[i]), so = [];
    for (let s = 0; s < 8; s++) {
      const y = er.slice(6 * s, 6 * s + 6), v = SB[s][(y[0] * 2 + y[5]) * 16 + y[1] * 8 + y[2] * 4 + y[3] * 2 + y[4]];
      so.push((v >> 3) & 1, (v >> 2) & 1, (v >> 1) & 1, v & 1);
    }
    const f = perm(so, P), nr = l.map((v, i) => v ^ f[i]); l = r; r = nr;
    if (tr) step('Round ' + (n + 1) + ' (key K' + (dir > 0 ? n + 1 : 16 - n) + '):  L = ' + bh(l) + '  R = ' + bh(r));
  }
  if (tr) step('Swap the halves, then the final permutation gives ' + hex(toBytes(perm(r.concat(l), FP))));
  return toBytes(perm(r.concat(l), FP));
}
