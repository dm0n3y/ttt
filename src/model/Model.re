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

let blank_square = {marked: None, winning: false};
let blank_subgrid = [
  blank_square,
  blank_square,
  blank_square,
  blank_square,
  blank_square,
  blank_square,
  blank_square,
  blank_square,
  blank_square,
];
let blank_grid = [
  blank_subgrid,
  blank_subgrid,
  blank_subgrid,
  blank_subgrid,
  blank_subgrid,
  blank_subgrid,
  blank_subgrid,
  blank_subgrid,
  blank_subgrid,
];

let rec get_item = (lst: list('a), index: int): 'a =>
  switch (lst, index) {
  | ([x, ..._], 0) => x
  | ([_, ...xs], n) => get_item(xs, n - 1)
  | ([], _) =>
    //debug info
    failwith("get_item: index out of bounds " ++ string_of_int(index))
  };

let init = {grid: blank_grid, player_turn: Player.X, active_subboard: None};

let line: list((int, int, int)) = [
  (0, 1, 2),
  (3, 4, 5),
  (6, 7, 8),
  (0, 3, 6),
  (1, 4, 7),
  (2, 5, 8),
  (0, 4, 8),
  (2, 4, 6),
];

let rec dye_board = (squarelst: list(square), n: int): list(square) => {
  switch (squarelst, n) {
  | ([], _) => []
  | ([x, ...xs], 0) =>
    let {marked, _} = x;
    [{marked, winning: true}] @ xs;
  | ([x, ...xs], n) => [x] @ dye_board(xs, n - 1)
  };
};

type sub_square = {
  subgrid,
  win: bool,
};

let small_squares = (g: subgrid): sub_square => {
  let squarelst =
    g
    |> List.map(square => {
         let {marked, _} = square;
         {marked, winning: false};
       });

  line
  |> List.filter_map(tri => {
       let (i, j, k) = tri;
       let a = get_item(g, i);
       let b = get_item(g, j);
       let c = get_item(g, k);
       switch (a.marked, b.marked, c.marked) {
       | (Some(p), Some(q), Some(r)) =>
         if (p == q && q == r) {
           Some((i, j, k));
         } else {
           None;
         }
       | _ => None
       };
     })
  |> (
    fun
    | [] => {subgrid: squarelst, win: false}
    | [w, ..._] => {
        let (i, j, k) = w;
        let squarelst = dye_board(squarelst, i);
        let squarelst = dye_board(squarelst, j);
        let squarelst = dye_board(squarelst, k);
        {subgrid: squarelst, win: true};
      }
  );
};

let squares = ({grid, _}: t): list(list(square)) => {
  grid
  |> List.map(g => {
       let {subgrid, _} = small_squares(g);
       subgrid;
     });
};
let player_turn = ({player_turn, _}: t): Player.t => player_turn;


let active_subboard: t => option(int) =
  ({active_subboard, _}: t) => active_subboard;

// required by Incr_dom
let cutoff = (===);
