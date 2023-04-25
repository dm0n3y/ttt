type square =
  | Unmarked
  | Marked(Player.t);

type grid = Grid.t(square);

type t = {
  board: grid,
  player_turn: Player.t,
};

// required by Incr_dom
let cutoff: (t, t) => bool;

// the initial model when the app first loads
let init: t;

/* return the winning player and their winning three-in-a-row if there is one */
let winner: grid => option((Player.t, Grid.three_in_a_row));
