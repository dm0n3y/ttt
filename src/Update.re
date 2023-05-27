open Base;

module Action = {
  [@deriving sexp]
  type t =
    | Mark((int, int));
};

let rec set_item = (g: list('a), index: int, item: 'a): list('a) => {
  switch (g, index) {
  | ([], _) => []
  | ([_, ...xs], 0) => [item] @ xs
  | ([x, ...xs], _) => [x] @ set_item(xs, index - 1, item)
  };
};
let update = (index: Action.t, state: Model.t): Model.t => {
  switch (index) {
  | Mark((a, b)) =>
    let target_grid = Model.get_item(state.grid, a);
    let new_square: Model.square = {
      marked: Some(state.player_turn),
      winning: false,
    };
    let new_subgrid = set_item(target_grid, b, new_square);
    let new_grid = set_item(state.grid, a, new_subgrid);
    let (next_subgrid, next_turn) =
      switch (Model.small_squares(new_subgrid).win) {
      | false => (Some(b), Player.toggle(state.player_turn))
      | true => (None, state.player_turn)
      };
    {grid: new_grid, player_turn: next_turn, active_subboard: next_subgrid};
  };
};
