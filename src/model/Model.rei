type square = {
  marked: option(Player.t),
  winning: bool,
};

type t;

//helps in view.re
let squares: t => list(list(square));
let player_turn: t => Player.t;
let active_subboard: t => option(int);

// required by Incr_dom
let cutoff: ('a, 'a) => bool;
