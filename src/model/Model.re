type square = {
  marked: option(Player.t),
  winning: bool,
};

type index = int;
type grid = list(square);
type t = {
  grid,
  player_turn: Player.t,
};

let blank_square = {marked: None, winning: false};
let blank_grid = [
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

let rec get_item = (lst: grid, index: index): square =>
  switch (lst, index) {
  | ([x, ..._], 0) => x
  | ([_, ...xs], n) => get_item(xs, n - 1)
  | ([], _) =>
    //debug info
    failwith("get_item: index out of bounds " ++ string_of_int(index))
  };

let init = {grid: blank_grid, player_turn: Player.X};

let line: list((index, index, index)) = [
  (0, 1, 2),
  (3, 4, 5),
  (6, 7, 8),
  (0, 3, 6),
  (1, 4, 7),
  (2, 5, 8),
  (0, 4, 8),
  (2, 4, 6),
];

let rec dye_board = (squarelst: list(square), n: index): list(square) => {
  switch (squarelst, n) {
  | ([], _) => []
  | ([x, ...xs], 0) =>
    let {marked, _} = x;
    [{marked, winning: true}] @ xs;
  | ([x, ...xs], n) => [x] @ dye_board(xs, n - 1)
  };
};

let squares = ({grid, _}: t): list(square) => {
  let squarelst =
    grid
    |> List.map(square => {
         let {marked, _} = square;
         {marked, winning: false};
       });
  line
  |> List.filter_map(tri => {
       let (i, j, k) = tri;
       let a = get_item(grid, i);
       let b = get_item(grid, j);
       let c = get_item(grid, k);
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
    | [] => squarelst
    | [w, ..._] =>
      {
        let (i, j, k) = w;
        let squarelst = dye_board(squarelst, i);
        let squarelst = dye_board(squarelst, j);
        let squarelst = dye_board(squarelst, k);
        squarelst;
      }
  );
};
let player_turn = ({player_turn, _}: t): Player.t => player_turn;

// required by Incr_dom
let cutoff = (===);
