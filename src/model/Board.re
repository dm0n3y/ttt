type row('square) = Triple.t('square);
type t('square) = Triple.t(row('square));

[@deriving sexp]
type row_index = Triple.index;
[@deriving sexp]
type col_index = Triple.index;
[@deriving sexp]
type square_index = (row_index, col_index);

let get_row = Triple.get_component;
let put_row = Triple.put_component;

let get_col = Triple.get_component;
let put_col = Triple.put_component;

let get_square = ((r, c): square_index, board: t('square)) =>
  board |> get_row(r) |> get_col(c);
let put_square = ((r, c): square_index, square: 'square, board: t('square)) => {
  let new_row = board |> get_row(r) |> put_col(c, square);
  board |> put_row(r, new_row);
};

let to_indexed_list = (board: t('square)): list((square_index, 'square)) => {
  let sq_indices =
    Triple.[
      (Zero, Zero),
      (Zero, One),
      (Zero, Two),
      (One, Zero),
      (One, One),
      (One, Two),
      (Two, Zero),
      (Two, One),
      (Two, Two),
    ];
  sq_indices
  |> List.map(sq_index => (sq_index, board |> get_square(sq_index)));
};
