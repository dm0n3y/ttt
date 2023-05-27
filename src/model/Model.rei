// represents the state of a square on the board
type square = {
  marked: option(Player.t),
  winning: bool,
};

// Model.t contain all relevant details regarding the current state of the game
// Notice the type of squares and player_turn 
type t;

// The initial state of the game
let init: t;

// a list of all the squares on the board
// You may need to attach winning information to each square here 
let squares: t => list(square);
// the player who is currently playing
let player_turn: t => Player.t;

// required by Incr_dom
let cutoff: ('a, 'a) => bool;
