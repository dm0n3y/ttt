type square = {
  marked: option(Player.t),
  winning: bool,
};

type t;

let squares: t => list(square);
let player_turn: t => Player.t;

// required by Incr_dom
let cutoff: ('a, 'a) => bool;
