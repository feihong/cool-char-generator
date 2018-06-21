type hanzi = {
  text: string,
  ordinal: int,
}

let randomIntRange = (min, max) =>
  Random.int(max - min + 1) + min;

[@bs.val] external fromCodePoint : int => string = "String.fromCodePoint";

let getHanzi = () => {
  let ordinal = randomIntRange(0x4e00, 0x9fff);
  let text = fromCodePoint(ordinal);
  {text, ordinal}
};
