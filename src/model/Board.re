type t('square) = Triple.t(Triple.t('square));

[@deriving sexp]
type square_index = (Triple.index, Triple.index);

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

let index_list: list(square_index) =
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

[@deriving sexp]
type three_in_a_row = Triple.t(square_index);
let threes_in_a_row: list(three_in_a_row) =
  Triple.[
    ((Zero, Zero), (Zero, One), (Zero, Two)),
    ((One, Zero), (One, One), (One, Two)),
    ((Two, Zero), (Two, One), (Two, Two)),
    ((Zero, Zero), (One, Zero), (Two, Zero)),
    ((Zero, One), (One, One), (Two, One)),
    ((Zero, Two), (One, Two), (Two, Two)),
    ((Zero, Zero), (One, One), (Two, Two)),
    ((Zero, Two), (One, One), (Two, Zero)),
  ];
