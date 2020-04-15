type t('square) = Triple.t(Triple.t('square));

[@deriving sexp]
type index = (Triple.index, Triple.index);

let get_row = Triple.get_component;
let put_row = Triple.put_component;

let get_col = Triple.get_component;
let put_col = Triple.put_component;

let get_square = ((r, c): index, board: t('square)) =>
  board |> get_row(r) |> get_col(c);
let put_square = ((r, c): index, square: 'square, board: t('square)) => {
  let new_row = board |> get_row(r) |> put_col(c, square);
  board |> put_row(r, new_row);
};

let index_list: list(index) = [
  (0, 0),
  (0, 1),
  (0, 2),
  (1, 0),
  (1, 1),
  (1, 2),
  (2, 0),
  (2, 1),
  (2, 2),
];

[@deriving sexp]
type three_in_a_row = Triple.t(index);
let threes_in_a_row: list(three_in_a_row) = [
  ((0, 0), (0, 1), (0, 2)),
  ((1, 0), (1, 1), (1, 2)),
  ((2, 0), (2, 1), (2, 2)),
  ((0, 0), (1, 0), (2, 0)),
  ((0, 1), (1, 1), (2, 1)),
  ((0, 2), (1, 2), (2, 2)),
  ((0, 0), (1, 1), (2, 2)),
  ((0, 2), (1, 1), (2, 0)),
];
