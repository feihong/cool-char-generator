open Belt;
open CoolCharData;

let str = ReasonReact.string;

/* State declaration */
type state = {
  chars: array(coolChar),
  mode: mode,  
  anchorEl: option(Dom.element),
  popupChar: coolChar,
};

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("CoolCharGenerator");

/* `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (_children) => {
  let getMode = mode =>
    /* If mode is `Any, then randomly pick a writing system */
    (mode == `Any) 
      ? coolWritingSystems |. Util.chooseFromArray
      : mode;

  let getCoolChar = mode => 
    switch(getMode(mode)) {
    | `Emoji => 
        Emoji.getEmoji() |> e => {
          text: e.text,
          caption: Printf.sprintf("%s (%s)", 
                                  e.shortname |. String.capitalize, 
                                  e.category |. String.capitalize),
        }
    | (`Hanzi|`Hangul|`Kana|`Devanagari|`Hieroglyphs|`Tibetan) as writingSys => 
        IntlChar.getIntlChar(writingSys) |> ic => {
          text: ic.text,
          caption: Printf.sprintf("%s %s", 
                                  ic.writingSystem, 
                                  ic.ordinal |. Util.numToHex),
        }
    | _ => {text: "?", caption: "?"}
    };

  let charClick = (evt, cc, self) => {
    let el = evt |. ReactEventRe.Mouse.target;
    (el, cc) |. OpenPopup |. self.ReasonReact.send;
  };

  /* Convert the given option(Dom.element) to the form preferred by 
     MaterialUi.Popover's anchorEl argument */
  let elemToObjGeneric = maybeEl =>
    maybeEl |. Option.map(el =>
      `ObjectGeneric(el |. ReactDOMRe.domElementToObj));
  {
    /* spread the other default fields of component here and override a few */
    ...component,

    initialState: () => {
      chars: [||],
      mode: `Any,
      anchorEl: None,
      popupChar: {text: "?", caption: "?"},
    },

    didMount: self => self.send(AddChar),

    /* State transitions */
    reducer: (action, state) => ReasonReact.(
      switch (action) {
        | AddChar => Update({
              ...state,
              chars: Array.concat([|getCoolChar(state.mode)|], state.chars)
            })
        | Clear => Update({...state, chars: [||]})
        | ChangeMode(mode) => Update({...state, mode: mode})
        | OpenPopup((el, cc)) => Update({...state, anchorEl: Some(el), popupChar: cc})
        | ClosePopup => Update({...state, anchorEl: None})
      }
    ),

    render: ({state, send} as self) => {
      <div>
        <MaterialUi.Popover open_=Option.isSome(state.anchorEl)
                          onClose=(_evt => send(ClosePopup))
                          anchorEl=?elemToObjGeneric(state.anchorEl)>
          <div className="popover-content">
            <div className="text">
              (str(state.popupChar.text))
            </div>
            <div className="caption">
              (str(state.popupChar.caption))
            </div>
          </div>
        </MaterialUi.Popover>
        <ControlPanel value=(state.mode |. modeToJs) send=send />        
        <div className="chars">
          (
            state.chars
            |. Array.mapWithIndex((i, cc) =>
                <span key=string_of_int(i) title=cc.caption 
                      onClick=(evt => charClick(evt, cc, self))>
                  (str(cc.text))
                </span>)
            |. ReasonReact.array
          )
        </div>
      </div>;
    },
  };
};