type square =
  | Unmarked
  | Marked(Player.t);

type grid = unit;

type t = unit;

type board = {
  squarelst: list((square, (int, int))),
  winning_line: option(((int, int), (int, int), (int, int))),
  player_turn: Player.t,
};

// required by Incr_dom
let cutoff = (===);

let init: t = failwith("todo");

let winner = failwith("todo");

let makeBoard = failwith("todo");
