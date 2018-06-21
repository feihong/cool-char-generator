open Belt;

module Emojione = {
  [@bs.deriving abstract]
  type emojioneItem = {
    uc_output: string,
    category: string,
  };

  [@bs.val] external emojioneList : Js.Dict.t(emojioneItem) = "emojione.emojioneList";
  [@bs.val] external convertUcOutput : string => string = "emojione.convert";

  let getItems = () =>
    Js.Dict.keys(emojioneList)
    |. Array.keepMap(shortname => {
        switch (Js.Dict.get(emojioneList, shortname)) {
        /* Reject flag emojis because they are boring */
        | Some(item) => (item |. category == "flags") ?
                          None : Some((shortname, item))
        | None => None
        };
      });
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
        /* Chop off first and last characters */
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