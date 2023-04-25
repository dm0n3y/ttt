type square =
  | Unmarked
  | Marked(Player.t);

type grid = Grid.t(square);

// Model of the Model-View-Update architecture
type t = {
  board: grid,
  player_turn: Player.t,
};

// required by Incr_dom
let cutoff = (===);

let empty_grid = failwith("todo");

let init = failwith("todo");

let winner = failwith("todo");
