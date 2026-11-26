// DES (ECB)
ALGORITHMS.push(
{ n: 'DES (ECB)', k: 'Key (exactly 8 bytes, e.g. 8 letters or digits)', t: 'Hello DES test!!', e: '12345678',
  h: 'Encrypts in 8 byte blocks and shows hex. Decrypt by pasting the hex. Short blocks get zero bytes.',
  f: ecb(8, 8, desKeys, desBlock) }
);
