module Vdom = Virtual_dom.Vdom;

let view_of_square =
    (
      ~inject: Update.Action.t => Vdom.Event.t,
      ~is_active: bool,
      subgrid_index: Grid.index,
      index: Grid.index,
      square: Model.square,
    )
    : Vdom.Node.t =>
  switch (square) {
  | Unmarked =>
    Vdom.Node.div(
      [
        Vdom.Attr.classes(["square"]),
        ...is_active
             ? [
               Vdom.Attr.on_click(_ =>
                 inject(Update.Action.MarkSquare(subgrid_index, index))
               ),
             ]
             : [],
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

let view_of_subgrid =
    (
      ~inject: Update.Action.t => Vdom.Event.t,
      ~is_active: bool,
      subgrid_index: Grid.index,
      subgrid: Model.subgrid,
    )
    : Vdom.Node.t => {
  let squares =
    Grid.index_list
    |> List.map(index =>
         view_of_square(
           ~inject,
           ~is_active,
           subgrid_index,
           index,
           subgrid |> Grid.get_item(index),
         )
       );
  let winner_marks =
    switch (Model.subgrid_winner(subgrid)) {
    | None => []
    | Some((p, three_in_a_row)) => [
        WinnerLine.view(three_in_a_row),
        PlayerMark.view(p),
      ]
    };
  Vdom.Node.div(
    [Vdom.Attr.classes(["subgrid", is_active ? "active" : "inactive"])],
    [GridLines.view] @ squares @ winner_marks,
  );
};

let view_of_grid =
    (
      ~inject: Update.Action.t => Vdom.Event.t,
      active_subgrid: option(Grid.index),
      grid: Model.grid,
    )
    : Vdom.Node.t => {
  let subgrids =
    Grid.index_list
    |> List.map(subgrid_index => {
         let subgrid = grid |> Grid.get_item(subgrid_index);
         let is_active =
           switch (Model.subgrid_winner(subgrid)) {
           | Some(_) => false
           | None =>
             switch (active_subgrid) {
             | None => true
             | Some(j) => j == subgrid_index
             }
           };
         view_of_subgrid(~inject, ~is_active, subgrid_index, subgrid);
       });
  let winner_line =
    Model.grid_winner(grid)
    |> Option.map(((_, three_in_a_row)) => WinnerLine.view(three_in_a_row))
    |> Option.to_list;
  Vdom.Node.div(
    [Vdom.Attr.classes(["grid"])],
    [GridLines.view] @ subgrids @ winner_line,
  );
};

let view = (~inject, model: Model.t) =>
  Vdom.Node.div(
    [Vdom.Attr.id("board"), cursor_attr(model.player_turn)],
    [view_of_grid(~inject, model.active_subgrid, model.board)],
  );
