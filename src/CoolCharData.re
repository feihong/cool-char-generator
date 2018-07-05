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

let dropdownOptions = Array.concat([|`Any|], coolWritingSystems);

type coolChar = {
  text: string,
  caption: string,
};

/* State declaration */
type state = {
  chars: array(coolChar),
  mode: mode,  
  anchorEl: option(Dom.element),
  popupChar: coolChar,
};

/* Action declaration */
type action =
  | AddChar
  | Clear
  | ChangeMode(mode)
  | OpenPopup((Dom.element, coolChar))   /* anchor element, popup char */
  | ClosePopup;
