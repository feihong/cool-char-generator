open Belt;

/* Convert Unicode code point to corresponding string */
[@bs.val] external fromCodePoint : int => string = "String.fromCodePoint";

/* Return an integer between min and max (inclusive) */
let randomIntRange = (min, max) =>
  Random.int(max - min + 1) + min;

/* Return random element from given array */
let chooseFromArray = array => {
  let index = array |. Array.length |. Random.int;
  array |. Array.getExn(index);
};

/* Convert given string to array of code points */
let stringToCodePoints: string => array(int) =
  [%bs.raw {|
    function (text) {
      return [...text].map(s => s.charCodeAt(0))
    }
  |}];

/* Equivalent to evt.target.value */
let eventTargetValue = evt => 
  (evt |. ReactEventRe.Form.target |. ReactDOMRe.domElementToObj)##value;
