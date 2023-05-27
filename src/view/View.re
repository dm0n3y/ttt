module Vdom = Virtual_dom.Vdom;
//import css file

let view_of_square =
    (
      ~inject: Update.Action.t => Vdom.Event.t,
      ~index: int,
      square: Model.square,
    )
    : Vdom.Node.t =>
  switch (square.marked) {
  | None =>
    let click_handlers = [
      Vdom.Attr.on_click(_ => inject(Update.Action.Mark(index))),
    ];
    Vdom.Node.div(
      [Vdom.Attr.classes(["square"]), ...click_handlers],
      [PlayerMark.view(square)],
    );
  | Some(_) =>
    Vdom.Node.div(
      [Vdom.Attr.classes(["square"])],
      [PlayerMark.view(square)],
    )
  };

let view = (~inject, model: Model.t) => {
  let rec mksquare = (sqlst: list(Model.square), index) => {
    switch (sqlst) {
    | [] => []
    | [sq, ...rest] =>
      let sqview = view_of_square(~inject, ~index, sq);
      [sqview, ...mksquare(rest, index + 1)];
    };
  };
  let sqview = mksquare(Model.squares(model), 0);

  Vdom.Node.div(
    [Vdom.Attr.id("board")],
    //[Vdom.Node.div([Vdom.Attr.classes(["grid"])], sqview)],
    [PlayerMark.grid_view(sqview)],
  );
};
