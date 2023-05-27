open Base;

module Action = {
  [@deriving sexp]
  type t =
    | Mark((int, int));
};

let update = failwith("todo");
