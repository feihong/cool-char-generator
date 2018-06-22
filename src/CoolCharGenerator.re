open Belt;

let str = ReasonReact.string;

let eventTargetValue = evt => 
  (evt |. ReactEventRe.Form.target |. ReactDOMRe.domElementToObj)##value;

type coolChar = {
  text: string,
  caption: string,
};

[@bs.deriving jsConverter]
type mode = [
  | `Hanzi
  | `Hangul
  | `Emoji
  | `Any
];

let modeFromJsEvent = evt =>
  switch (eventTargetValue(evt) |. modeFromJs) {
  | None => `Any
  | Some(mode) => mode
  };

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

let getMode = (mode) =>
  /* If mode is `Either, then randomly pick `Hanzi or `Emoji */
  if (mode == `Any) {
    switch (Random.int(2)) {
    | 0 => `Hanzi
    | _ => `Emoji
    }
  } else
    mode;

let getCoolChar = mode => 
  switch(getMode(mode)) {
  | `Emoji => {
      let emoji = Emoji.getEmoji();
      {
        text: emoji.text,
        caption: Printf.sprintf("%s (%s)", emoji.shortname, emoji.category),
      }
    }
  | (`Hanzi | `Hangul) as language => {
      let ic = IntlChar.getIntlChar(language);
      {
        text: ic.text,
        caption: Printf.sprintf("Type: %s, Code point: %d", 
                                ic.language, ic.ordinal),
      }      
    }
  | _ => {text: "?", caption: "?"}
  };

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (_children) => {
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
      <option value=modeStr>
        (str(modeStr))
      </option>
    };

    <div>
      <div className="form-inline">
        <select className="form-control mr-2"
                value=modeToJs(state.mode)
                onChange=(evt => evt |. modeFromJsEvent |. ChangeMode |. send)>
          (changeModeOption(`Hanzi))
          (changeModeOption(`Hangul))
          (changeModeOption(`Emoji))
          (changeModeOption(`Any))
        </select>
        <button className="btn btn-primary btn-sm mr-2"
                onClick=(_ => send(AddChar))>
          (str("Generate"))
        </button>
        <button className="btn btn-primary btn-sm"
                onClick=(_ => send(Clear))>
          (str("Clear"))
        </button>
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
