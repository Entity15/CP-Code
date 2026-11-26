// ---------- Hill cipher helpers ----------
const minor = (m, r, c) => m.filter((_, i) => i != r).map(row => row.filter((_, j) => j != c));
const det = m => m.length == 1 ? m[0][0] : m[0].reduce((s, v, c) => s + (c % 2 ? -1 : 1) * v * det(minor(m, 0, c)), 0);
const inv26 = a => { for (let x = 1; x < 26; x++) if (mod(a * x) == 1) return x; return -1; };
function hillInverse(m) {
  const di = inv26(mod(det(m)));
  if (di < 0) throw Error('This key has no inverse mod 26. Try another.');
  return m.map((_, i) => m.map((_, j) => mod(di * mod(((i + j) % 2 ? -1 : 1) * det(minor(m, j, i))))));
}
