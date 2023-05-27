module Action: {
  [@deriving sexp]
  type t =
    | Mark((int, int));
};

let update: (Action.t, Model.t) => Model.t;
