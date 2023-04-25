type t('item) = Triple.t(Triple.t('item));

[@deriving sexp]
type index = (Triple.index, Triple.index);

type t('item) = Triple.t(Triple.t('item));

[@deriving sexp]
type index = (Triple.index, Triple.index);

let get_item = failwith("todo");
let put_item = failwith("todo");

let index_list = failwith("todo");

[@deriving sexp]
type three_in_a_row = Triple.t(index);
let threes_in_a_row = failwith("todo");
