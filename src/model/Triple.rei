[@deriving sexp]
type t('c) = ('c, 'c, 'c);

[@deriving sexp]
type index = int;

let get_component: (index, t('c)) => 'c;
let put_component: (index, 'c, t('c)) => t('c);

let map: ('a => 'b, t('a)) => t('b);
