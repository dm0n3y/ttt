module Action = {
  [@deriving sexp]
  type t =
    | MarkSquare(Board.square_index);
};

let update = (action: Action.t, model: Model.t): Model.t =>
  switch (action) {
  | MarkSquare(sq_index) =>
    let next_board =
      model.board
      |> Board.put_square(sq_index, Model.Marked(model.player_turn));
    let next_turn = Player.toggle(model.player_turn);
    {board: next_board, player_turn: next_turn};
  };
