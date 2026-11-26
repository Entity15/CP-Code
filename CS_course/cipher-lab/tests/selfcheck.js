// Run with: node tests/selfcheck.js
// Loads the cipher files the same way the page does and checks known answers and round trips.
const vm = require('vm'), fs = require('fs'), path = require('path');
const root = path.join(__dirname, '..');
const html = fs.readFileSync(path.join(root, 'index.html'), 'utf8');
const files = [...html.matchAll(/<script src="([^"]+)"/g)].map(m => m[1]).filter(f => f !== 'js/app.js' && f !== 'js/config.js');
const ctx = vm.createContext({ TextEncoder, TextDecoder, crypto: globalThis.crypto });
for (const f of files) vm.runInContext(fs.readFileSync(path.join(root, f), 'utf8'), ctx, { filename: f });
vm.runInContext('globalThis.go = (n, t, k, d) => { STEPS.length = 0; return ALGORITHMS.find(a => a.n.startsWith(n)).f(t, k, d); };', ctx);
const go = ctx.go;
let bad = 0;
const check = (name, ok) => { if (!ok) bad++; console.log((ok ? 'PASS ' : 'FAIL ') + name); };
const last = s => s.split('\n').pop();

check('SHA-1 abc', go('SHA-1', 'abc', '', 1) === 'a9993e364706816aba3e25717850c26c9cd0d89d');
check('AES known answer', go('AES', 'Two One Nine Two', 'Thats my Kung Fu', 1) === '29c3505f571420f6402299b31a02d73a');
check('Vigenere known answer', go('Vigen', 'ATTACK AT DAWN', 'LEMON', 1) === 'LXFOPV EF RNHR');
check('Hill known answer', go('Hill', 'ACT', '6 24 1 13 16 10 20 17 15', 1) === 'POH');

const trips = [['Caesar', 'Hello World', '3'], ['Stream', 'Hello World', 'KEY'], ['Vigen', 'ATTACK AT DAWN', 'LEMON'],
  ['Autokey', 'ATTACK AT DAWN', 'QUEENLY'], ['Vernam', 'Hello', 'KEYKEY'], ['Hill', 'HELP', '3 3 2 5'],
  ['RSA', 'Hi!', '61 53 17'], ['AES', 'Hello, world! 1234567890', 'Thats my Kung Fu'], ['DES', 'Hello DES!', 'secret12']];
for (const [n, t, k] of trips) check('round trip ' + n, last(go(n, last(go(n, t, k, 1)), k, -1)) === t);
for (const [n, t, k] of [['Playfair', 'HIDE THE GOLD', 'MONARCHY'], ['Columnar', 'WEAREDISCOVERED', 'ZEBRAS']])
  check('round trip ' + n + ' (padding allowed)', last(go(n, last(go(n, t, k, 1)), k, -1)).startsWith(t.replace(/ /g, '')));

const fails = (n, t, k) => { try { go(n, t, k, 1); return false; } catch (e) { return true; } };
check('AES rejects short key', fails('AES', 'x', 'short'));
check('Stream rejects non-letter key', fails('Stream', 'Hello', 'K3Y'));
check('Hill rejects singular key', fails('Hill', 'ABC', '2 4 6 8'));
console.log(bad ? bad + ' check(s) failed' : 'All checks passed');
process.exit(bad ? 1 : 0);
