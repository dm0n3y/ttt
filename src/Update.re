open Base;

module Action = {
  [@deriving sexp]
  type t =
    | Mark(int);
};

let rec set_item = (g: Model.grid, index: int, item: Player.t): Model.grid => {
  switch (g, index) {
  | ([], _) => []
  | ([_, ...xs], 0) => [{Model.marked: Some(item), winning: false}] @ xs
  | ([x, ...xs], _) => [x] @ set_item(xs, index - 1, item)
  };
};
let update = (index: Action.t, state: Model.t): Model.t => {
  switch (index) {
  | Mark(index) =>
    let new_grid = set_item(state.grid, index, state.player_turn);
    let new_player = Player.toggle(state.player_turn);
    {grid: new_grid, player_turn: new_player};
  };
};
