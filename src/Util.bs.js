// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE

import * as Random from "bs-platform/lib/es6/random.js";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";

function randomIntRange(min, max) {
  return Random.$$int((max - min | 0) + 1 | 0) + min | 0;
}

function chooseFromArray(array) {
  var index = Random.$$int(array.length);
  return Belt_Array.getExn(array, index);
}

var stringToCodePoints = (
    function (text) {
      return [...text].map(s => s.charCodeAt(0))
    }
  );

function eventTargetValue(evt) {
  return evt.target.value;
}

export {
  randomIntRange ,
  chooseFromArray ,
  stringToCodePoints ,
  eventTargetValue ,
  
}
/* stringToCodePoints Not a pure module */