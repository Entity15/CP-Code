// AES-128 (ECB)
ALGORITHMS.push(
{ n: 'AES-128 (ECB)', k: 'Key (exactly 16 bytes, e.g. 16 letters or digits)', t: 'Two One Nine Two', e: 'Thats my Kung Fu',
  h: 'Encrypts in 16 byte blocks and shows hex. Decrypt by pasting the hex. Short blocks get zero bytes.',
  f: ecb(16, 16, aesKeys, aesBlock) }
);
