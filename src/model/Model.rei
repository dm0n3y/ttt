type square = {
  marked: option(Player.t),
  winning: bool,
};

type index = (int, int);
type subgrid = list(square);
type grid = list(list(square));
type t = {
  grid,
  player_turn: Player.t,
  active_subboard: option(int),
};

type sub_square = {
  subgrid,
  win: bool,
};
let init: t;
let small_squares: subgrid => sub_square;
let squares: t => list(list(square));
let player_turn: t => Player.t;
let active_subboard: t => option(int);
let get_item: (list('a), int) => 'a;
// required by Incr_dom
let cutoff: ('a, 'a) => bool;
