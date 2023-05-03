module Action: {
  [@deriving sexp]
  type t =
    | MarkSquare((int, int));
};

let update: (Action.t, Model.t) => Model.t;
