module Vdom = Virtual_dom.Vdom;

let view_of_square =
    (
      ~inject: Update.Action.t => Vdom.Event.t,
      index: Board.index,
      square: Model.square,
    )
    : Vdom.Node.t =>
  switch (square) {
  | Unmarked =>
    Vdom.Node.div(
      [
        Vdom.Attr.classes(["square"]),
        Vdom.Attr.on_click(_ => inject(Update.Action.MarkSquare(index))),
      ],
      [],
    )
  | Marked(p) =>
    Vdom.Node.div([Vdom.Attr.classes(["square"])], [PlayerMark.view(p)])
  };

let cursor_attr = (p: Player.t) =>
  Vdom.Attr.create(
    "style",
    switch (p) {
    | X => "cursor: url(cursor-x.svg), pointer;"
    | O => "cursor: url(cursor-o.svg), pointer;"
    },
  );

let view =
    (~inject: Update.Action.t => Vdom.Event.t, model: Model.t): Vdom.Node.t => {
  let squares =
    Board.index_list
    |> List.map(index =>
         view_of_square(
           ~inject,
           index,
           model.board |> Board.get_square(index),
         )
       );
  let winner_line =
    model |> Model.winner |> Option.map(WinnerLine.view) |> Option.to_list;
  Vdom.Node.div(
    [Vdom.Attr.id("board"), cursor_attr(model.player_turn)],
    [Grid.view] @ squares @ winner_line,
  );
};
