open Belt;

[@bs.deriving jsConverter]
type mode = [
  | `Hanzi
  | `Hangul
  | `Kana
  | `Devanagari
  | `Hieroglyphs
  | `Tibetan
  | `Emoji
  | `Any
];

let coolWritingSystems: array(mode) = [|
  `Hanzi, `Hangul, `Kana, `Devanagari, `Hieroglyphs, `Tibetan, `Emoji,
|];

let options = Array.concat([|`Any|], coolWritingSystems);

/* Action declaration */
type action =
  | AddChar
  | Clear
  | ChangeMode(mode);
