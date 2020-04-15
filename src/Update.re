module Action = {
  [@deriving sexp]
  type t =
    | MarkSquare(Grid.index, Grid.index);
};

let update = (action: Action.t, model: Model.t): Model.t =>
  switch (action) {
  | MarkSquare(subgrid_index, square_index) =>
    let next_subgrid =
      model.board
      |> Grid.get_item(subgrid_index)
      |> Grid.put_item(square_index, Model.Marked(model.player_turn));
    let next_grid = model.board |> Grid.put_item(subgrid_index, next_subgrid);
    let next_turn = Player.toggle(model.player_turn);
    {board: next_grid, player_turn: next_turn};
  };
