// AES and DES both work block by block (ECB). Text is padded with zero bytes, output is hex.
const ecb = (size, keyLen, makeKeys, block) => (t, k, d) => {
  const kb = enc8(k);
  if (kb.length != keyLen) throw Error('The key must be exactly ' + keyLen + ' bytes (letters and digits count as 1 byte each)');
  const ks = makeKeys(kb); let b = d > 0 ? enc8(t) : unhex(t), o = [];
  while (b.length % size) b.push(0);
  for (let i = 0; i < b.length; i += size) o.push(...block(b.slice(i, i + size), ks, d));
  if (d > 0) return hex(o);
  while (o.length && !o[o.length - 1]) o.pop();
  return dec8(o);
};
