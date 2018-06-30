open Belt;
open CoolCharData;

let str = ReasonReact.string;

let component = ReasonReact.statelessComponent("ControlPanel");

let make = (~value, ~send, _children) => {
  let modeFromJsEvent = evt =>
    switch (evt |. Util.eventTargetValue |. modeFromJs) {
    | Some(mode) => mode
    | None => `Any
    };
  {
    ...component,

    render: _self => MaterialUi.(
      <Grid container=true spacing=V16>
        <Grid item=true>
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
        </Grid>
        <Grid item=true>
          <MaterialUi.Button color=`Primary variant=`Raised
                onClick=(_ => send(AddChar))>
            (str("Generate"))
          </MaterialUi.Button>
        </Grid>
        <Grid item=true>
          <MaterialUi.Button color=`Secondary variant=`Raised
                onClick=(_ => send(Clear))>
            (str("Clear"))
          </MaterialUi.Button>
        </Grid>
      </Grid>
    )
  }
};