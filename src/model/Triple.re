open Sexplib.Std;

[@deriving sexp]
type t('c) = ('c, 'c, 'c);

[@deriving sexp]
type index = int;

let get_component = (i, (c0, c1, c2)) =>
  switch (i) {
  | 0 => c0
  | 1 => c1
  | _two => c2
  };
let put_component = (i, c, (c0, c1, c2)) =>
  switch (i) {
  | 0 => (c, c1, c2)
  | 1 => (c0, c, c2)
  | _two => (c0, c1, c)
  };

let map = (f, (c0, c1, c2)) => (f(c0), f(c1), f(c2));
