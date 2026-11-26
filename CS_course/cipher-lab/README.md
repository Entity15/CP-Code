# Cipher Room

A small web page that runs 13 classic ciphers in the browser, plus the C++ versions of the same programs.

## How to run

1. Open this folder in VS Code.
2. Right-click `index.html` and choose "Open with Live Server".

No install and no internet are needed. Nothing is sent anywhere.

## How to use it

1. Pick a cipher in the dropdown. It fills in an example and shows what the key should look like.
2. Press **Encrypt?**. The label changes to **Encrypt!** and the result appears in the output field.
3. If `allowDecrypt` is on in `js/config.js`, a **Decrypt?** button fades in. Press it and the original text appears below.
4. If `showSteps` is on in `js/config.js`, the **Steps** box at the bottom shows the working for Vernam, Playfair, Hill, columnar transposition, RSA, AES, DES and SHA-1.

SHA-1 is a hash, so its button says **Hash?** and there is nothing to decrypt.

Vernam and the one-time pad are the same method (XOR with a key). The **Random key** button makes a random key as long as your text. Used only once, that is a true one-time pad.

## Ciphers

Caesar, Stream, Vigenère, Autokey, Vernam / One-Time Pad, Hill (2x2 and 3x3), Playfair, Columnar Transposition, RSA, AES-128 (ECB), DES (ECB) and SHA-1.

## Folder map

- `index.html` is the page.
- `css/style.css` is the look.
- `js/config.js` holds the page settings (`allowDecrypt` and `showSteps`, both off by default).
- `js/app.js` is the page logic (dropdown and buttons).
- `js/lib/` holds the shared helpers, the AES and DES tables, and the list that the ciphers register in.
- `js/ciphers/` has one file per cipher. To add a cipher, copy one of these, change it, and add a `<script>` line to `index.html`.
- `cpp/` has the C++ programs for the same ciphers.
- `tests/selfcheck.js` runs the known answers below plus encrypt/decrypt round trips. Run it with `node tests/selfcheck.js`.

## Quick self-checks

These are known answers, so you can tell the ciphers work.

- SHA-1 of `abc` is `a9993e364706816aba3e25717850c26c9cd0d89d`.
- AES with text `Two One Nine Two` and key `Thats my Kung Fu` gives `29c3505f571420f6402299b31a02d73a`.
- Vigenère with `ATTACK AT DAWN` and key `LEMON` gives `LXFOPV EF RNHR`.
- Hill with `ACT` and key `6 24 1 13 16 10 20 17 15` gives `POH`.

## Limits

- AES and DES key lengths are counted in bytes, so a key with accented letters needs fewer characters.
- The Stream cipher key can only contain letters.
- Playfair treats J as I, so `JUMP` comes back as `IUMP`. Playfair, Hill and columnar add X as padding, and it can show up at the end of the decrypted text.
- AES and DES remove trailing zero bytes when decrypting, so text that really ends in a zero byte loses it.

These are teaching versions. AES and DES use ECB mode with zero padding, RSA has no padding and works on one character at a time, and SHA-1 is no longer safe for real security work.
