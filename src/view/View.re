module Vdom = Virtual_dom.Vdom;

let view_of_square =
    (
      ~inject: Update.Action.t => Vdom.Event.t,
      index: Board.square_index,
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

let view =
    (~inject: Update.Action.t => Vdom.Event.t, model: Model.t): Vdom.Node.t => {
  let board_view =
    Board.index_list
    |> List.map(sq_index =>
         view_of_square(
           ~inject,
           sq_index,
           model.board |> Board.get_square(sq_index),
         )
       );
  let winner_line_view =
    model |> Model.winner |> Option.map(WinnerLine.view) |> Option.to_list;
  Vdom.Node.div([Vdom.Attr.id("board")], board_view @ winner_line_view);
};
