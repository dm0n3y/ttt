type square =
  | Unmarked
  | Marked(Player.t);

type t = {
  board: Grid.t(square),
  player_turn: Player.t,
};

// required by Incr_dom
let cutoff = (===);

let init: t = {
  player_turn: X,
  board: (
    (Unmarked, Unmarked, Unmarked),
    (Unmarked, Unmarked, Unmarked),
    (Unmarked, Unmarked, Unmarked),
  ),
};

let winner = (model: t): option(Grid.three_in_a_row) =>
  Grid.threes_in_a_row
  |> List.filter_map(three_in_a_row => {
       let (i0, i1, i2) = three_in_a_row;
       switch (
         model.board |> Grid.get_square(i0),
         model.board |> Grid.get_square(i1),
         model.board |> Grid.get_square(i2),
       ) {
       | (Marked(p0), Marked(p1), Marked(p2)) when p0 == p1 && p1 == p2 =>
         Some(three_in_a_row)
       | _ => None
       };
     })
  |> (
    fun
    | [] => None
    | [three_in_a_row, ..._] => Some(three_in_a_row)
  );
