module Vdom = Virtual_dom.Vdom;

let view_of_square =
    (
      ~inject: Update.Action.t => Vdom.Event.t,
      ~is_active: bool,
      ~index: (int, int),
      square: Model.square,
    )
    : Vdom.Node.t =>
  switch (square) {
  | Unmarked =>
    let click_handlers =
      is_active
        ? [
          Vdom.Attr.on_click(_ => inject(Update.Action.MarkSquare(index))),
        ]
        : [];
    Vdom.Node.div([Vdom.Attr.classes(["square"]), ...click_handlers], []);
  | Marked(p) =>
    Vdom.Node.div([Vdom.Attr.classes(["square"])], [PlayerMark.view(p)])
  };

let view_of_grid =
    (~inject: Update.Action.t => Vdom.Event.t, grid: Model.t): Vdom.Node.t => {
  let board = Model.makeBoard(grid);
  let squares =
    board.squarelst
    |> List.map(squs => {
         let (squ, index) = squs;
         let is_active =
           switch (board.winning_line) {
           | Some(_) => false
           | None => true
           };
         view_of_square(~inject, ~is_active, ~index, squ);
       });
  let winner_line =
    board.winning_line
    |> Option.map(three_in_a_row => WinnerLine.view(three_in_a_row))
    |> Option.to_list;
  Vdom.Node.div(
    [Vdom.Attr.classes(["grid"])],
    [GridLines.view] @ squares @ winner_line,
  );
};

let view = (~inject, model: Model.t) => {
  let cursor_attr =
    Vdom.Attr.create(
      "style",
      switch (Model.makeBoard(model).player_turn) {
      | X => "cursor: url(cursor-x.svg), pointer;"
      | O => "cursor: url(cursor-o.svg), pointer;"
      },
    );
  Vdom.Node.div(
    [Vdom.Attr.id("board"), cursor_attr],
    [view_of_grid(~inject, model)],
  );
};
