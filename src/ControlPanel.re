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
                dropdownOptions 
                |. Array.map(mode => mode |. modeToJs |. label =>                  
                    <MenuItem key=label value=`String(label)>
                      (str(label))
                    </MenuItem>
                   )
              )
            </Select>
          </FormControl>
        </Grid>
        <Grid item=true>
          <Button color=`Primary variant=`Raised
                onClick=(_ => send(AddChar))>
            (str("Generate"))
          </Button>
        </Grid>
        <Grid item=true>
          <Button color=`Secondary variant=`Raised
                onClick=(_ => send(Clear))>
            (str("Clear"))
          </Button>
        </Grid>
      </Grid>
    )
  }
};