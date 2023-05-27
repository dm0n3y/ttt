open Base;

module Action = {
  [@deriving sexp]
  type t =
    | Mark(int);
};

let update = failwith("TODO");