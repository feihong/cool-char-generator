// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE

import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Js_mapperRt from "bs-platform/lib/es6/js_mapperRt.js";

var jsMapperConstantArray = /* array */[
  /* tuple */[
    -790390071,
    "Tibetan"
  ],
  /* tuple */[
    -325826967,
    "Hangul"
  ],
  /* tuple */[
    3257036,
    "Any"
  ],
  /* tuple */[
    50782054,
    "Emoji"
  ],
  /* tuple */[
    83233512,
    "Hieroglyphs"
  ],
  /* tuple */[
    90688528,
    "Devanagari"
  ],
  /* tuple */[
    836565865,
    "Kana"
  ],
  /* tuple */[
    894130468,
    "Hanzi"
  ]
];

function modeToJs(param) {
  return Js_mapperRt.binarySearch(8, param, jsMapperConstantArray);
}

function modeFromJs(param) {
  return Js_mapperRt.revSearch(8, jsMapperConstantArray, param);
}

var coolWritingSystems = /* array */[
  /* Hanzi */894130468,
  /* Hangul */-325826967,
  /* Kana */836565865,
  /* Devanagari */90688528,
  /* Hieroglyphs */83233512,
  /* Tibetan */-790390071,
  /* Emoji */50782054
];

var dropdownOptions = Belt_Array.concat(/* array */[/* Any */3257036], coolWritingSystems);

export {
  modeToJs ,
  modeFromJs ,
  coolWritingSystems ,
  dropdownOptions ,
  
}
/* dropdownOptions Not a pure module */
