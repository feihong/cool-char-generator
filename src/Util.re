/* Return an integer between min and max (inclusive) */
let randomIntRange = (min, max) =>
  Random.int(max - min + 1) + min;

/* Convert Unicode code point to corresponding string */
[@bs.val] external fromCodePoint : int => string = "String.fromCodePoint";