open Virtual_dom.Vdom;

let view_of_square = (~inject, ~index: int, square: Model.square): Node.t =>
  switch (square.marked) {
  | None =>
    let click_handlers = [
      Attr.on_click(_ => inject(Update.Action.Mark(index))),
    ];
    Node.div(
      ~attr=Attr.many([Attr.classes(["square"]), ...click_handlers]), //only empty square can be clicked
      [Square.view(square)],
    );
  | Some(_) =>
    Node.div(
      ~attr=Attr.many([Attr.classes(["square"])]),
      [Square.view(square)],
    )
  };

// `view_of_grid(squares)` will arrange the given `squares` into 3x3 grid
let view_of_grid = (squares: list(Node.t)): Node.t =>
  Node.div(~attr=Attr.class_("grid"), squares);

// TODO
let view = (~inject, model: Model.t) => {
  Node.div(~attr=Attr.id("board"), [view_of_grid([])]);
};
