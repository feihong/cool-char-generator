// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE

import * as Random from "bs-platform/lib/es6/random.js";
import * as $$String from "bs-platform/lib/es6/string.js";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Util$ReactTemplate from "./Util.bs.js";

function getItems() {
  return Belt_Array.keepMap(Object.keys(emojione.emojioneList), (function (shortname) {
                var match = emojione.emojioneList[shortname];
                if (match !== undefined) {
                  var match$1 = match.category !== "flags";
                  if (match$1) {
                    return /* Some */[/* tuple */[
                              shortname,
                              match
                            ]];
                  } else {
                    return /* None */0;
                  }
                } else {
                  return /* None */0;
                }
              }));
}

var Emojione = /* module */[/* getItems */getItems];

var emojis = Belt_Array.map(getItems(/* () */0), (function (param) {
        var item = param[1];
        var shortname = param[0];
        var len = shortname.length;
        return /* record */[
                /* shortname */Util$ReactTemplate.String_[/* replace */1]($$String.sub(shortname, 1, len - 2 | 0), "_", " "),
                /* text */emojione.convert(item.uc_output),
                /* category */item.category
              ];
      }));

function getEmoji() {
  var index = Random.$$int(emojis.length);
  return Belt_Array.getExn(emojis, index);
}

export {
  Emojione ,
  emojis ,
  getEmoji ,
  
}
/* emojis Not a pure module */
