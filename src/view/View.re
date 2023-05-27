module Vdom = Virtual_dom.Vdom;
//import css file

let view_of_square =
    (
      ~inject: Update.Action.t => Vdom.Event.t,
      ~index: (int, int),
      ~active: bool,
      square: Model.square,
    )
    : Vdom.Node.t =>
  switch (square.marked) {
  | None =>
    let click_handlers =
      active
        ? [Vdom.Attr.on_click(_ => inject(Update.Action.Mark(index)))] : [];
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
  //TODO
  Vdom.Node.div([Vdom.Attr.id("board")], []);
};
