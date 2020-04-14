type square =
  | Unmarked
  | Marked(Player.t);

type t = {
  board: Board.t(square),
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

let winner = (model: t): option((Player.t, Board.three_in_a_row)) =>
  Board.threes_in_a_row
  |> List.filter_map(three_in_a_row => {
       let (i0, i1, i2) = three_in_a_row;
       switch (
         model.board |> Board.get_square(i0),
         model.board |> Board.get_square(i1),
         model.board |> Board.get_square(i2),
       ) {
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
