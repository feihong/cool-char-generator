open Belt;
open CoolCharData;

let str = ReasonReact.string;

let component = ReasonReact.statelessComponent("Dropdown");

let make = (~value, ~send, _children) => {
  let modeFromJsEvent = evt =>
    switch (evt |. Util.eventTargetValue |. modeFromJs) {
    | Some(mode) => mode
    | None => `Any
    };
  {
    ...component,

    render: _self => MaterialUi.(
      <FormControl>
        <Select value=`String(value) 
                onChange=((evt, _) => 
                  evt |. modeFromJsEvent |. ChangeMode |. send)>
          (
            options 
            |. Array.map(mode => {
              let modeStr = mode |. modeToJs;
              <MenuItem key=modeStr value=`String(modeStr)>
                (str(modeToJs(mode)))
              </MenuItem>
            })
            |. ReasonReact.array
          )
        </Select>
      </FormControl>
    )
  }
};