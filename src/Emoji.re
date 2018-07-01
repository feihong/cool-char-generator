open Belt;

/* We use the emojione library because emoji code points are not in a contiguous
   code block, and emojione provides a full dataset of emojis that allows us
   to filter out the numerious boring flag emojis.
*/
module Emojione = {
  [@bs.deriving abstract]
  type emojioneItem = {
    uc_output: string,
    category: string,
  };

  [@bs.val] external emojioneList : Js.Dict.t(emojioneItem) = "emojione.emojioneList";
  [@bs.val] external convertUcOutput : string => string = "emojione.convert";

  /* Return array of (shortname, emojioneItem) tuples */
  let getItems = () =>
    Js.Dict.keys(emojioneList)
    |. Array.keepMap(shortname => 
        switch (Js.Dict.get(emojioneList, shortname)) {
        /* Reject flag emojis because they are boring */
        | Some(item) => (item |. category != "flags") 
                        ? Some((shortname, item))
                        : None
        | None => None
        }
      );
}

type emoji = {
  shortname: string,
  text: string,
  category: string,
};

let emojis = Emojione.(
  getItems()
  |. Array.map(((shortname, item)) => {
      let len = String.length(shortname);
      {
        /* Chop off the colons at the beginning and */
        shortname: shortname |. String.sub(1, len - 2),
        text: item |. uc_output |. convertUcOutput,
        category: item |. category,
      }
    })
);

let getEmoji = () => {
  let index = emojis |. Array.length |. Random.int;
  emojis |. Array.getExn(index);
};