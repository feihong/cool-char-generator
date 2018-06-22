type intlChar = {
  text: string,
  language: string,
  ordinal: int,
};

[@bs.deriving jsConverter]
type language = [
  | `Hanzi
  | `Hangul
  | `Kana
];

let getCharFromRange = (min, max) => {
  let ordinal = Util.randomIntRange(min, max);
  let text = Util.fromCodePoint(ordinal);
  (text, ordinal)
};

let kanaCodePoints: array(int) = [%bs.raw {|
  [...'゠ァアィイゥウェエォオカグケゲコゴサザシジスズセダチヂッツヅテデトドナニバパヒビピフブプヘベペホムメモャヤュユョヨラリルヰヱヲンヴヵヶヷヸヹヺぁあぃいぅうぇえぉおかぐけげこごさざしじすずせだちぢっつづてでとどなにばぱひびぴふぶぷへべぺほむめもゃやゅゆょよらりるゐゑをんゔゕゖ']
  .map(s => s.charCodeAt(0))
|}];

let getIntlChar = lang => {
  let (text, ordinal) = 
    switch (lang) {
    | `Hanzi => getCharFromRange(0x4e00, 0x9fff)
    /* https://en.wikipedia.org/wiki/Hangul_Syllables */  
    | `Hangul => getCharFromRange(0xAC00, 0xD7AF)
    | `Kana => 
        let ordinal_ = Util.chooseFromArray(kanaCodePoints);
        (Util.fromCodePoint(ordinal_), ordinal_);
  };
  let languageStr = languageToJs(lang);
  {text, ordinal, language: languageStr}
};
