type square =
  | Unmarked
  | Marked(Player.t);

type grid = Grid.t(square);

// Model of the Model-View-Update architecture
type t = {
  board: grid,
  player_turn: Player.t,
};

// required by Incr_dom
let cutoff = (===);

let empty_grid = (
  (Unmarked, Unmarked, Unmarked),
  (Unmarked, Unmarked, Unmarked),
  (Unmarked, Unmarked, Unmarked),
);

let init: t = {player_turn: X, board: empty_grid};

let winner = (grid: grid): option((Player.t, Grid.three_in_a_row)) =>
  Grid.threes_in_a_row
  |> List.filter_map(three_in_a_row => {
       let (square0, square1, square2) =
         three_in_a_row |> Triple.map(i => grid |> Grid.get_item(i));
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
