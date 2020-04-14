type square =
  | Unmarked
  | Marked(Player.t);

type t = {
  board: Board.t(square),
  player_turn: Player.t,
};

// required by Incr_dom
let cutoff = (===);

let init = {
  player_turn: X,
  board: (
    (Unmarked, Unmarked, Unmarked),
    (Unmarked, Unmarked, Unmarked),
    (Unmarked, Unmarked, Unmarked),
  ),
};
