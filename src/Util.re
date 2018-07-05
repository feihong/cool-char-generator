open Belt;

module String = {
  include String;

  /* Convert Unicode code point to corresponding string */
  [@bs.val] external fromCodePoint: int => string = "String.fromCodePoint";

  /* Convert given string to array of code points */
  let toCodePoints: string => array(int) =
    [%raw (text) => {|      
      return [...text].map(s => s.charCodeAt(0))      
    |}];

  /* Global string replace */
  let replace: (string, string, string) => string = 
    [%raw (s, a, b) => {|      
      return s.replace(new RegExp(a, 'g'), b)      
    |}];
};

/* Return an integer between min and max (inclusive) */
let randomIntRange = (min, max) =>
  Random.int(max - min + 1) + min;

/* Return random element from given array */
let chooseFromArray = array => {
  let index = array |. Array.length |. Random.int;
  array |. Array.getExn(index);
};

/* Equivalent to evt.target.value */
let eventTargetValue = evt =>
  (evt |. ReactEventRe.Form.target |. ReactDOMRe.domElementToObj)##value;

[@bs.send] external numToString: (int, int) => string = "toString";

let numToHex = x => 
  numToString(x, 16) |. String.uppercase |. x => "0x" ++ x;
