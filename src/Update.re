module Action = {
  [@deriving sexp]
  type t =
    | MarkSquare(Grid.index, Grid.index);
};

let update = (action: Action.t, model: Model.t): Model.t =>
  switch (action) {
  | MarkSquare(subgrid_index, square_index) =>
    let new_subgrid =
      model.board
      |> Grid.get_item(subgrid_index)
      |> Grid.put_item(square_index, Model.Marked(model.player_turn));
    let new_grid = model.board |> Grid.put_item(subgrid_index, new_subgrid);
    let (next_subgrid, next_turn) =
      switch (
        model.board |> Grid.get_item(square_index) |> Model.subgrid_winner
      ) {
      | None => (Some(square_index), Player.toggle(model.player_turn))
      | Some(_) => (None, model.player_turn)
      };
    {board: new_grid, active_subgrid: next_subgrid, player_turn: next_turn};
  };
