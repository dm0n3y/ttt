open Virtual_dom.Vdom;

let view_of_square =
    (
      ~inject,
      ~is_active: bool,
      ~index as (subgrid_index, square_index): (Grid.index, Grid.index),
      square: Model.square,
    )
    : Node.t =>
  switch (square) {
  | Unmarked =>
    let click_handlers =
      is_active
        ? [
          Attr.on_click(_ =>
            inject(Update.Action.MarkSquare(subgrid_index, square_index))
          ),
        ]
        : [];
    Node.div(~attr=Attr.(many([class_("square"), ...click_handlers])), []);
  | Marked(p) =>
    Node.div(~attr=Attr.class_("square"), [PlayerMark.view(p)])
  };

let view_of_subgrid =
    (
      ~inject,
      ~is_active: bool,
      ~index as subgrid_index: Grid.index,
      subgrid: Model.subgrid,
    )
    : Node.t => {
  let squares =
    Grid.index_list
    |> List.map(square_index =>
         subgrid
         |> Grid.get_item(square_index)
         |> view_of_square(
              ~inject,
              ~is_active,
              ~index=(subgrid_index, square_index),
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
  Node.div(
    ~attr=Attr.classes(["subgrid", is_active ? "active" : "inactive"]),
    [GridLines.view] @ squares @ winner_marks,
  );
};

let view_of_grid =
    (~inject, ~active_subgrid: option(Grid.index), grid: Model.grid): Node.t => {
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
         view_of_subgrid(~inject, ~is_active, ~index=subgrid_index, subgrid);
       });
  let winner_line =
    Model.grid_winner(grid)
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
