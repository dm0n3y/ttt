type square = {
  marked: option(Player.t),
  winning: bool,
};

type t = unit;

let squares = failwith("TODO")
let player_turn = failwith("TODO")

// required by Incr_dom
let cutoff = (===);
