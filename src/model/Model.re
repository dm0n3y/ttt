type square =
  | Unmarked
  | Marked(Player.t);

type subgrid = Grid.t(square);
type grid = Grid.t(subgrid);

type t = {
  board: grid,
  active_subgrid: option(Grid.index),
  player_turn: Player.t,
};

// required by Incr_dom
let cutoff = (===);

let empty_subgrid = (
  (Unmarked, Unmarked, Unmarked),
  (Unmarked, Unmarked, Unmarked),
  (Unmarked, Unmarked, Unmarked),
);

let init: t = {
  player_turn: X,
  active_subgrid: None,
  board: (
    (empty_subgrid, empty_subgrid, empty_subgrid),
    (empty_subgrid, empty_subgrid, empty_subgrid),
    (empty_subgrid, empty_subgrid, empty_subgrid),
  ),
};

let subgrid_winner =
    (subgrid: subgrid): option((Player.t, Grid.three_in_a_row)) =>
  subgrid
  |> Grid.has_three_in_a_row(
       ~item_val=
         fun
         | Unmarked => None
         | Marked(p) => Some(p),
     );

let grid_winner = (grid: grid): option((Player.t, Grid.three_in_a_row)) =>
  grid
  |> Grid.has_three_in_a_row(~item_val=subgrid =>
       subgrid_winner(subgrid) |> Option.map(((p, _)) => p)
     );
