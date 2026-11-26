// Page logic: the dropdown, the Encrypt? / Encrypt! button, and the Decrypt? / Decrypt! step.
// ($ comes from js/lib/helpers.js, and ALGORITHMS is filled by the files in js/ciphers.)

const sel = $('alg'), txt = $('txt'), key = $('key'), out = $('out'), note = $('note');
const stepsBox = $('stepsBox'), stepsOut = $('steps'), rand = $('rand');
const encBtn = $('enc'), decBtn = $('dec'), decWrap = $('decWrap'), backWrap = $('backWrap'), back = $('back');
let encrypted = '';   // what the last Encrypt! produced, so Decrypt! can use it

ALGORITHMS.forEach((a, i) => sel.add(new Option(a.n, i)));
const current = () => ALGORITHMS[sel.value];

// Some ciphers (RSA) put a line of info first. Split it from the real result.
function split(a, s) {
  if (!a.info) return ['', s];
  const i = s.indexOf('\n');
  return [s.slice(0, i), s.slice(i + 1)];
}

// Show an element with the fade-in. Taking the class off and putting it back restarts the fade.
function reveal(el) {
  el.hidden = false;
  el.classList.remove('reveal');
  void el.offsetWidth;
  el.classList.add('reveal');
}

// Back to the starting state: labels reset, output cleared, decrypt step hidden
function reset() {
  const a = current();
  encBtn.textContent = a.hash ? 'Hash?' : 'Encrypt?';
  decBtn.textContent = 'Decrypt?';
  out.value = ''; back.value = ''; note.textContent = '';
  out.classList.remove('bad'); back.classList.remove('bad');
  decWrap.hidden = true; backWrap.hidden = true;
  encrypted = '';
  STEPS.length = 0; stepsBox.hidden = true;
}

// Choosing a cipher fills in its example, hint and key label
function pick() {
  const a = current();
  $('hint').textContent = a.h;
  $('lk').textContent = a.k;
  $('keyRow').hidden = !a.k;
  rand.hidden = !a.random;
  txt.value = a.t;
  key.value = a.e;
  reset();
}

encBtn.onclick = () => {
  const a = current();
  reset();
  encBtn.textContent = a.hash ? 'Hash!' : 'Encrypt!';
  try {
    const [info, result] = split(a, a.f(txt.value, key.value, 1));
    out.value = result;
    note.textContent = info;
    encrypted = result;
    showSteps(a.hash ? 'Steps to hash' : 'Steps to encrypt');
    if (!a.hash && SETTINGS.allowDecrypt) reveal(decWrap);   // a hash cannot be decrypted, so no Decrypt? for SHA-1
  } catch (e) {
    out.value = e.message;
    out.classList.add('bad');
    encBtn.textContent = a.hash ? 'Hash?' : 'Encrypt?';
  }
};

decBtn.onclick = () => {
  if (!SETTINGS.allowDecrypt) return;
  const a = current();
  decBtn.textContent = 'Decrypt!';
  back.classList.remove('bad');
  STEPS.length = 0;
  try {
    back.value = split(a, a.f(encrypted, key.value, -1))[1];
  } catch (e) {
    back.value = e.message;
    back.classList.add('bad');
  }
  showSteps('Steps to decrypt');
  reveal(backWrap);
};

// Changing the cipher starts over. Changing the text or the key only resets the buttons and results.
// Show the working that the cipher wrote with step(). Ciphers without steps just hide the box.
function showSteps(title) {
  if (!SETTINGS.showSteps || !STEPS.length) { stepsBox.hidden = true; return; }
  stepsOut.textContent = title + '\n\n' + STEPS.join('\n');
  stepsBox.open = true;
  reveal(stepsBox);
}

// A random key as long as the text, made with the browser's secure random numbers
rand.onclick = () => {
  const set = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
  const nums = crypto.getRandomValues(new Uint32Array(Math.max(1, enc8(txt.value).length)));
  key.value = [...nums].map(x => set[x % set.length]).join('');
  reset();
};

sel.onchange = pick;
txt.oninput = reset;
key.oninput = reset;

pick();
