// ---------- small helpers ----------
const $ = id => document.getElementById(id);
const mod = (x, m = 26) => ((x % m) + m) % m;
const isL = c => /[a-z]/i.test(c);
const val = c => c.toUpperCase().charCodeAt(0) - 65;      // A=0 ... Z=25
const kv = c => isL(c) ? val(c) : 0;                       // key letter -> shift
const letters = s => s.toUpperCase().replace(/[^A-Z]/g, '');
const need = (s, m) => { if (!s) throw Error(m || 'Please fill in the key'); };
// move one letter by s places, keep its case, leave other characters alone
const shift = (c, s) => {
  const b = c >= 'a' && c <= 'z' ? 97 : c >= 'A' && c <= 'Z' ? 65 : 0;
  return b ? String.fromCharCode(b + mod(c.charCodeAt(0) - b + s)) : c;
};
const enc8 = s => [...new TextEncoder().encode(s)];
const dec8 = b => new TextDecoder().decode(Uint8Array.from(b));
const hex = b => b.map(x => x.toString(16).padStart(2, '0')).join('');
const unhex = s => {
  s = s.replace(/\s/g, '');
  if (!/^([0-9a-f]{2})+$/i.test(s)) throw Error('Paste the hex text from the Encrypt step');
  return s.match(/../g).map(x => parseInt(x, 16));
};

// Steps: a cipher calls step('text') to show its working. The page empties the list before each run.
const STEPS = [];
const step = s => STEPS.push(s);
