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
  };
  let label = writingSystemToJs(writingSys);
  {text, ordinal, writingSystem: label}
};
