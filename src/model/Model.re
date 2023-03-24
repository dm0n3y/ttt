type square =
  | Unmarked
  | Marked(Player.t);

type subgrid = Grid.t(square);
type grid = Grid.t(subgrid);

// Model of the Model-View-Update architecture
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

let empty_grid = (
  (empty_subgrid, empty_subgrid, empty_subgrid),
  (empty_subgrid, empty_subgrid, empty_subgrid),
  (empty_subgrid, empty_subgrid, empty_subgrid),
);

let init: t = {player_turn: X, active_subgrid: None, board: empty_grid};

let subgrid_winner =
    (subgrid: subgrid): option((Player.t, Grid.three_in_a_row)) =>
  Grid.threes_in_a_row
  |> List.filter_map(three_in_a_row => {
       let (square0, square1, square2) =
         three_in_a_row |> Triple.map(i => subgrid |> Grid.get_item(i));
       switch (square0, square1, square2) {
       | (Marked(p0), Marked(p1), Marked(p2)) when p0 == p1 && p1 == p2 =>
         Some((p0, three_in_a_row))
       | _ => None
       };
     })
  |> (
    fun
    | [] => None
    | [winner, ..._] => Some(winner)
  );

let grid_winner = (grid: grid): option((Player.t, Grid.three_in_a_row)) => {
  let flat_grid =
    grid
    |> Grid.map(subgrid =>
         switch (subgrid_winner(subgrid)) {
         | None => Unmarked
         | Some((p, _)) => Marked(p)
         }
       );
  subgrid_winner(flat_grid);
};
