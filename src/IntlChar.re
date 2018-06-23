type intlChar = {
  text: string,
  writingSystem: string,
  ordinal: int,
};

[@bs.deriving jsConverter]
type writingSystem = [
  | `Hanzi
  | `Hangul
  | `Kana
  | `Devanagari
  | `Hieroglyphs
  | `Cuneiform    /* unfortunately, these are rather ugly */
  | `OldPersian   /* I'm on the fence about these */
];

let getCharFromRange = (min, max) => {
  let ordinal = Util.randomIntRange(min, max);
  let text = Util.fromCodePoint(ordinal);
  (text, ordinal)
};

let getCharFromCodePoints = codePoints => {
  let ordinal = Util.chooseFromArray(codePoints);
  let text = Util.fromCodePoint(ordinal);
  (text, ordinal)
};
  

let kanaCodePoints = [%bs.raw {|
  '゠ァアィイゥウェエォオカグケゲコゴサザシジスズセダチヂッツヅテデトドナニバパヒビピフブプヘベペホムメモャヤュユョヨラリルヰヱヲンヴヵヶヷヸヹヺぁあぃいぅうぇえぉおかぐけげこごさざしじすずせだちぢっつづてでとどなにばぱひびぴふぶぷへべぺほむめもゃやゅゆょよらりるゐゑをんゔゕゖ'
|}] |. Util.stringToCodePoints;

let devanagariCodePoints = [%bs.raw {|
  'ऄअआइईउऊऋऌऍऎएऐऑऒओऔकखगघङचछजझञटठडढणतथदधनऩपफबभमयरऱलळऴवशषसहऽॐक़ख़ग़ज़ड़ढ़फ़य़ॠॡ१२३४५६७८९ॲॳॴॵॶॷॸॹॺॻॼॽॾॿ'
|}] |. Util.stringToCodePoints;

/* The characters for Old Persian can't be pasted into a code editor, so we
   just use the code points directly */
let oldPersianCodePoints = [|
  66464, 66465, 66466, 66467, 66468, 66469, 66470, 66471, 66472, 66473, 66474, 66475, 66476, 66477, 66478, 66479, 66480, 66481, 66482, 66483, 66484, 66485, 66486, 66487, 66488, 66489, 66490, 66491, 66492, 66493, 66494, 66495, 66496, 66497, 66498, 66499, 66504, 66505, 66506, 66507, 66508, 66509, 66510, 66511, 66512, 66513, 66514, 66515, 66516, 66517
|];

Js.log(oldPersianCodePoints);

let getIntlChar = writingSys => {
  let (text, ordinal) = 
    switch (writingSys) {
    | `Hanzi => getCharFromRange(0x4e00, 0x9fff)
    /* https://en.wikipedia.org/wiki/Hangul_Syllables */  
    | `Hangul => getCharFromRange(0xAC00, 0xD7AF)
    | `Kana => getCharFromCodePoints(kanaCodePoints)
    /* https://en.wikipedia.org/wiki/Devanagari_(Unicode_block) */
    | `Devanagari => getCharFromCodePoints(devanagariCodePoints)
    /* https://en.wikipedia.org/wiki/Egyptian_Hieroglyphs_(Unicode_block) */
    | `Hieroglyphs => getCharFromRange(0x13000, 0x1342E)
    /* https://en.wikipedia.org/wiki/Cuneiform_(Unicode_block) */
    | `Cuneiform => getCharFromRange(0x12000, 0x123FF)
    /* https://en.wikipedia.org/wiki/Old_Persian_(Unicode_block) */
    | `OldPersian => getCharFromCodePoints(oldPersianCodePoints)
  };
  let label = writingSystemToJs(writingSys);
  {text, ordinal, writingSystem: label}
};
