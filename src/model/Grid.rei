type t('item) = Triple.t(Triple.t('item));

[@deriving sexp]
type index = (Triple.index, Triple.index);
let index_list: list(index);

let get_item: (index, t('i)) => 'i;
let put_item: (index, 'i, t('i)) => t('i);

type three_in_a_row = Triple.t(index);
let threes_in_a_row: list(three_in_a_row);
