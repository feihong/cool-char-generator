open Belt;
open CoolCharData;

let str = ReasonReact.string;

type coolChar = {
  text: string,
  caption: string,
};

/* State declaration */
type state = {
  chars: array(coolChar),
  mode: mode,
};

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("CoolCharGenerator");

/* `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (_children) => {
  let getMode = mode =>
    /* If mode is `Any, then randomly pick a writing system */
    if (mode == `Any) {
      coolWritingSystems |. Util.chooseFromArray
    } else {
      mode
    }

  let getCoolChar = mode => 
    switch(getMode(mode)) {
    | `Emoji => {
        let emoji = Emoji.getEmoji();
        {
          text: emoji.text,
          caption: Printf.sprintf("%s (%s)", emoji.shortname, emoji.category),
        }
      }
    | (`Hanzi|`Hangul|`Kana|`Devanagari|`Hieroglyphs|`Tibetan) as writingSys => {
        let ic = IntlChar.getIntlChar(writingSys);
        {
          text: ic.text,
          caption: Printf.sprintf("Writing system: %s, Code point: %d", 
                                  ic.writingSystem, ic.ordinal),
        }      
      }
    | _ => {text: "?", caption: "?"}
    };
  {
    /* spread the other default fields of component here and override a few */
    ...component,

    initialState: () => {
      chars: [||],
      mode: `Any,
    },

    didMount: self => self.send(AddChar),

    /* State transitions */
    reducer: (action, state) => ReasonReact.(
      switch (action) {
        | AddChar => Update({
              ...state,
              chars: Array.concat(state.chars, [|getCoolChar(state.mode)|])
            })
        | Clear => Update({...state, chars: [||]})
        | ChangeMode(mode) => Update({...state, mode: mode})
      }
    ),

    render: ({state, send}) => {
      <div>
        <ControlPanel value=(state.mode |. modeToJs) send=send />        
        <div className="chars">
          (
            state.chars
            |. Array.mapWithIndex((i, cc) =>
                <span key=string_of_int(i) title=cc.caption>
                  (str(cc.text))
                </span>)
            |> ReasonReact.array
          )
        </div>
      </div>;
    },
  };
};