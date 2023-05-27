type square = {
  marked: option(Player.t),
  winning: bool,
};

type t = unit;

let squares = failwith("todo");
let player_turn = failwith("todo");
let active_subboard = failwith("todo");
// required by Incr_dom
let cutoff = (===);
