open Belt;

let str = ReasonReact.string;

type coolChar = {
  text: string,
  caption: string,
};

[@bs.deriving jsConverter]
type mode = [
  | `Hanzi
  | `Hangul
  | `Kana
  | `Devanagari
  | `Hieroglyphs
  | `Tibetan
  | `Emoji
  | `Any
];

let coolWritingSystems = [|
  `Hanzi, `Hangul, `Kana, `Devanagari, `Hieroglyphs, `Tibetan, `Emoji,
|];

let options = Array.concat([|`Any|], coolWritingSystems);

/* State declaration */
type state = {
  chars: array(coolChar),
  mode: mode,
};

/* Action declaration */
type action =
  | AddChar
  | Clear
  | ChangeMode(mode);

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("CoolCharGenerator");

/* `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (_children) => {
  let modeFromJsEvent = evt =>
    switch (evt |. Util.eventTargetValue |. modeFromJs) {
    | Some(mode) => mode
    | None => `Any
    };

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
      let changeModeOption = (mode) => {
        let modeStr = modeToJs(mode);
        <option key=modeStr value=modeStr>
          (str(modeStr))
        </option>
      };

      <div>
        <div className="form-inline">
          <select className="form-control mr-2"
                  value=modeToJs(state.mode)
                  onChange=(evt => evt |. modeFromJsEvent |. ChangeMode |. send)>
            (
              options
              |. Array.map(changeModeOption)
              |. ReasonReact.array
            )
          </select>
          <MaterialUi.Button color=`Primary variant=`Raised
                             onClick=(_ => send(AddChar))>
            (str("Generate"))
          </MaterialUi.Button>
          <MaterialUi.Button color=`Secondary variant=`Raised
                             onClick=(_ => send(Clear))>
            (str("Clear"))
          </MaterialUi.Button>
        </div>
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