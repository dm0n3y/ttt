type t('item) = Triple.t(Triple.t('item));

[@deriving sexp]
type index = (Triple.index, Triple.index);

let get_row = Triple.get_component;
let put_row = Triple.put_component;

let get_col = Triple.get_component;
let put_col = Triple.put_component;

let get_item = ((r, c): index, grid: t('item)) =>
  grid |> get_row(r) |> get_col(c);
let put_item = ((r, c): index, item: 'item, grid: t('item)) => {
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

let has_three_in_a_row =
    (~item_val: 'item => option('v), grid: t('item))
    : option(('v, three_in_a_row)) =>
  threes_in_a_row
  |> List.filter_map(three_in_a_row => {
       let (opt_v0, opt_v1, opt_v2) =
         three_in_a_row
         |> Triple.map(i => grid |> get_item(i))
         |> Triple.map(item_val);
       switch (opt_v0, opt_v1, opt_v2) {
       | (Some(v0), Some(v1), Some(v2)) when v0 == v1 && v1 == v2 =>
         Some((v0, three_in_a_row))
       | _ => None
       };
     })
  |> (
    fun
    | [] => None
    | [r, ..._] => Some(r)
  );
