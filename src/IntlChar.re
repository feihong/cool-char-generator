/**
 * Unicode code block references:
 * 
 * https://en.wikipedia.org/wiki/CJK_Unified_Ideographs_(Unicode_block)
 * https://en.wikipedia.org/wiki/Katakana_(Unicode_block)
 * https://en.wikipedia.org/wiki/Hiragana_(Unicode_block)
 * https://en.wikipedia.org/wiki/Hangul_Syllables
 * https://en.wikipedia.org/wiki/Devanagari_(Unicode_block)
 * https://en.wikipedia.org/wiki/Egyptian_Hieroglyphs_(Unicode_block)
 * https://en.wikipedia.org/wiki/Cuneiform_(Unicode_block)
 * https://en.wikipedia.org/wiki/Old_Persian_(Unicode_block)
 * https://en.wikipedia.org/wiki/Tibetan_(Unicode_block)
 * 
 */

open Util;

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
  | `Tibetan
  | `Cuneiform    /* unfortunately, these are rather ugly */
  | `OldPersian   /* these aren't that good-looking either */
];

let getCharFromRange = (min, max) => {
  let ordinal = Util.randomIntRange(min, max);
  let text = String.fromCodePoint(ordinal);
  (text, ordinal)
};

let getCharFromCodePoints = codePoints => {
  let ordinal = Util.chooseFromArray(codePoints);
  let text = String.fromCodePoint(ordinal);
  (text, ordinal)
};

let kanaCodePoints = [%bs.raw {|
  'ァアィイゥウェエォオカグケゲコゴサザシジスズセダチヂッツヅテデトドナニバパヒビピフブプヘベペホムメモャヤュユョヨラリルヰヱヲンヴヵヶヷヸヹヺぁあぃいぅうぇえぉおかぐけげこごさざしじすずせだちぢっつづてでとどなにばぱひびぴふぶぷへべぺほむめもゃやゅゆょよらりるゐゑをんゔゕゖ'
|}] |. String.toCodePoints;

let devanagariCodePoints = [%bs.raw {|
  'ऄअआइईउऊऋऌऍऎएऐऑऒओऔकखगघङचछजझञटठडढणतथदधनऩपफबभमयरऱलळऴवशषसहऽॐकखगजडढफयॠॡ१२३४५६७८९ॲॳॴॵॶॷॸॹॺॻॼॽॾॿ'
|}] |. String.toCodePoints;

let tibetanCodePoints = [%bs.raw {|
  'ༀ༁༂༃༄༅༆༇༈༉༊༒༓༔༕༖༗༘༜༡༢༣༤༥༦༧༨༩༪༫༬༭༮༯༰༱༲༳༴༸༺༻༼༽ཀཁགགངཅཆཇཉཊཋཌཌཎཏཐདདནཔཕབབམཙཚཛཛཝཞཟའཡརལཤཥསཧཨཀཪཫཬིཻོཽྀ྅ྈྉྊྋ྿࿂࿃࿄࿅࿇࿈࿉࿊࿋࿌࿏࿐࿑࿓࿔࿕࿖࿗࿘'
|}] |. String.toCodePoints;

/* The characters for Old Persian can't be pasted into a code editor, so we
   just use the code points directly */
let oldPersianCodePoints = [|
  66464, 66465, 66466, 66467, 66468, 66469, 66470, 66471, 66472, 66473, 66474, 66475, 66476, 66477, 66478, 66479, 66480, 66481, 66482, 66483, 66484, 66485, 66486, 66487, 66488, 66489, 66490, 66491, 66492, 66493, 66494, 66495, 66496, 66497, 66498, 66499, 66504, 66505, 66506, 66507, 66508, 66509, 66510, 66511, 66512, 66513, 66514, 66515, 66516, 66517
|];

let getIntlChar = writingSys => {
  let (text, ordinal) = 
    switch (writingSys) {
    | `Hanzi => getCharFromRange(0x4e00, 0x9fff)
    | `Hangul => getCharFromRange(0xAC00, 0xD7AF)
    | `Kana => getCharFromCodePoints(kanaCodePoints)
    | `Devanagari => getCharFromCodePoints(devanagariCodePoints)
    | `Hieroglyphs => getCharFromRange(0x13000, 0x1342E)
    | `Cuneiform => getCharFromRange(0x12000, 0x123FF)
    | `OldPersian => getCharFromCodePoints(oldPersianCodePoints)
    | `Tibetan => getCharFromCodePoints(tibetanCodePoints)
  };
  let label = writingSystemToJs(writingSys);
  {text, ordinal, writingSystem: label}
};
