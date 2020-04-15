module Action = {
  [@deriving sexp]
  type t =
    | MarkSquare(Grid.index);
};

let update = (action: Action.t, model: Model.t): Model.t =>
  switch (action) {
  | MarkSquare(index) =>
    let new_grid =
      model.board |> Grid.put_item(index, Model.Marked(model.player_turn));
    let next_turn = Player.toggle(model.player_turn);
    {board: new_grid, player_turn: next_turn};
  };
