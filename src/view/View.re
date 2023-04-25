open Virtual_dom.Vdom;

let view_of_square =
    (
      ~inject,
      ~is_active: bool,
      ~index: Grid.index,
      square: Model.square,
    )
    : Node.t =>
  switch (square) {
  | Unmarked =>
    let click_handlers =
      is_active
        ? [
          Attr.on_click(_ => inject(Update.Action.MarkSquare(index))),
        ]
        : [];
    Node.div(~attr=Attr.(many([class_("square"), ...click_handlers])), []);
  | Marked(p) =>
    Node.div(~attr=Attr.class_("square"), [PlayerMark.view(p)])
  };

let view_of_grid =
    (~inject, grid: Model.grid): Node.t => {
  let squares =
    Grid.index_list
    |> List.map(index => {
         let square = grid |> Grid.get_item(index);
         let is_active =
           switch (Model.winner(grid)) {
           | Some(_) => false
           | None => true
           };
         view_of_square(~inject, ~is_active, ~index, square);
       });
  let winner_line =
    Model.winner(grid)
    |> Option.map(((_, three_in_a_row)) => WinnerLine.view(three_in_a_row))
    |> Option.to_list;
  Node.div(
    ~attr=Attr.class_("grid"),
    [GridLines.view] @ subgrids @ winner_line,
  );
};

// View of the Model-View-Update architecture
let view = (~inject, model: Model.t) => {
  let cursor_attr =
    Attr.create(
      "style",
      switch (model.player_turn) {
      | X => "cursor: url(cursor-x.svg), pointer;"
      | O => "cursor: url(cursor-o.svg), pointer;"
      },
    );
  Node.div(
    ~attr=Attr.(many([id("board"), cursor_attr])),
    [
      view_of_grid(~inject, ~active_subgrid=model.active_subgrid, model.board),
    ],
  );
};
