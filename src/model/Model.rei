type square =
  | Unmarked
  | Marked(Player.t);

type grid; //optional

type t;

type board = {
  squarelst: list((square, (int, int))),
  winning_line: option(((int, int), (int, int), (int, int))),
  player_turn: Player.t,
};

let cutoff: ('a, 'a) => bool;

let init: t;

let winner:
  grid => option((Player.t, ((int, int), (int, int), (int, int))));

let makeBoard: t => board; //used in view
