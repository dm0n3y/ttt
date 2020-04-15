type t('item) = Triple.t(Triple.t('item));

[@deriving sexp]
type index = (Triple.index, Triple.index);

let get_row = Triple.get_component;
let put_row = Triple.put_component;

let get_col = Triple.get_component;
let put_col = Triple.put_component;

let get_square = ((r, c): index, grid: t('item)) =>
  grid |> get_row(r) |> get_col(c);
let put_square = ((r, c): index, item: 'item, grid: t('item)) => {
  let new_row = grid |> get_row(r) |> put_col(c, item);
  grid |> put_row(r, new_row);
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
