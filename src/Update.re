open Base;

module Action = {
  [@deriving sexp]
  type t =
    | MarkSquare((int, int));
};

let update = failwith("todo");
