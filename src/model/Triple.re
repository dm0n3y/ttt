[@deriving sexp]
type t('c) = ('c, 'c, 'c);

[@deriving sexp]
type index =
  | Zero
  | One
  | Two;

let get_component = (i: index, (c0, c1, c2)) =>
  switch (i) {
  | Zero => c0
  | One => c1
  | Two => c2
  };
let put_component = (i: index, c, (c0, c1, c2)) =>
  switch (i) {
  | Zero => (c, c1, c2)
  | One => (c0, c, c2)
  | Two => (c0, c1, c)
  };
